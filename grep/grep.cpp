#include "grep.hpp"

void grep::skip_whitespace() {
    while (command_index < command.size() && std::isspace(command[command_index])) {
        ++command_index;
    }
}

std::string grep::extract_word() {
    std::string result;
    skip_whitespace();
    if (command_index < command.size() && command[command_index] == '"') {
        ++command_index; 
        while (command_index < command.size() && command[command_index] != '"') {
            result += command[command_index++];
        }
        if (command_index < command.size() && command[command_index] == '"') {
            ++command_index;
        }
    }
    else {
        while (command_index < command.size() && !std::isspace(command[command_index])) {
            result += command[command_index++];
        }
    }
    return result;
}

void grep::parse_flags(){
    while(command_index<command.size() && command[command_index]=='-'){
        ++command_index;
        while(command_index<command.size() && std::isalpha(command[command_index])){
            char f=command[command_index++];
            switch(f){
                case 'i': ignore_case = true; 
                break;
                case 'n': show_line_numbers = true; 
                break;
                case 'v': invert_match = true; 
                break;
                case 'c': count_only = true; 
                break;
                case 'l': list_filenames_only = true; 
                break;
                case 'h': suppress_filename = true; 
                break;
                default:
                    std::cerr << "Unknown flag: -" << f << "\n";
                    break;
            }
        }
    }    
    skip_whitespace();
}

grep::grep(const std::string& cmd) : command(cmd) {
    command_index = 4;
    skip_whitespace();
    parse_flags();
    pattern = extract_word();
    skip_whitespace();
    while (command_index < command.size()) {
        std::string file = extract_word();
        if (!file.empty()) {
            filenames.push_back(file);
        }
        skip_whitespace();
    }
}

std::string grep::to_lower_str(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}

bool grep::match_pattern(const std::string& line) {
    std::string search_line = ignore_case ? to_lower_str(line) : line;
    std::string search_pattern = ignore_case ? to_lower_str(pattern) : pattern;
    return search_line.contains(search_pattern);
}

void grep::run() {
    for (const auto& filename : filenames) {
        std::fstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Couldn't open the file: " << filename << "\n";
            continue;
        }
        std::string content;
        char ch;
        while (file.get(ch)) {
            content += ch;
        }
        file.close();
        size_t content_index = 0;
        size_t line_number = 0;
        size_t match_count = 0;
        bool has_matches = false;
        std::string output;
        while (content_index < content.size()) {
            std::string line;
            while (content_index < content.size() && content[content_index] != '\n') {
                line += content[content_index++];
            }
            if (content_index < content.size() && content[content_index] == '\n') {
                line += content[content_index++];
            }
            line_number++;
            bool matched = match_pattern(line);
            if (invert_match) {
                matched = !matched;
            }
            if (matched) {
                has_matches = true;
                match_count++;
            }
            if (list_filenames_only && matched) {
                output = filename + "\n";
                break;
            }
            if (count_only) {
                continue;
            }
            if (matched && !list_filenames_only) {
                std::string line_output;
                if (!suppress_filename && filenames.size() > 1) {
                    line_output += "\033[35m" + filename + "\033[36m:\033[0m";
                }
                if (show_line_numbers) {
                    line_output += "\033[32m" + std::to_string(line_number) + "\033[36m:\033[0m";
                }
                size_t line_index = 0;
                std::string search_line = ignore_case ? to_lower_str(line) : line;
                std::string search_pattern = ignore_case ? to_lower_str(pattern) : pattern;
                while (line_index < line.size()) {
                    size_t pos = search_line.find(search_pattern, line_index);
                    if (pos >= search_line.size()) {
                        line_output += line.substr(line_index);
                        break;
                    }
                    line_output += line.substr(line_index, pos - line_index);
                    line_output += "\033[31m" + line.substr(pos, pattern.size()) + "\033[0m";
                    line_index = pos + pattern.size();
                }
                if (line.back() != '\n') {
                    line_output += '\n';
                }
                output += line_output;
            }
        }
        if (count_only && !list_filenames_only) {
            if (!suppress_filename && filenames.size() > 1) {
                output += "\033[35m" + filename + "\033[36m:\033[0m";
            }
            output += std::to_string(match_count) + "\n";
        } 
        else if (list_filenames_only && has_matches) {
            output = filename + "\n";
        }
        std::cout << output;
    }
}