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

void grep::run() {
    std::cout << "Flag: " << flag << "\n";
    std::cout << "Pattern: " << pattern << "\n";
    for(auto& filename : filenames){
        std::cout << "Filename: " << filename << "\n";
        std::fstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Couldn't open the file\n";
            return;
        }
        char ch;
        std::string content;
        while (file.get(ch)) {
            content += ch;
        }
        size_t content_index = 0;
        while (content_index < content.size()) {
            std::string line;
            while (content_index < content.size() && content[content_index] != '\n') {
                line += content[content_index++];
            }
            if (content_index < content.size() && content[content_index] == '\n') {
                line += content[content_index++];
            }
            bool matched = false;
            std::string line_output;
            size_t line_index = 0;
            std::string output;
            while (line_index < line.size()) {
                size_t i = line_index;
                size_t j = 0;
                while (i < line.size() && j < pattern.size() && line[i] == pattern[j]) {
                    i++;
                    j++;
                }
                if (j == pattern.size()) {
                    matched = true;
                    line_output += "\033[31m";
                    for (size_t k = 0; k < pattern.size(); ++k) {
                        line_output += pattern[k];
                    }
                    line_output += "\033[0m";
                    line_index += pattern.size();
                } 
                else {
                    line_output += line[line_index++];
                }
            }
            if (matched) {
                output += line_output;
                if (line.back() != '\n') {
                    output += '\n';
                }
            }
            std::cout << output;
        }
    }
}

grep::grep(const std::string& cmd) : command(cmd) {
    command_index = 4;
    skip_whitespace();
    if (command[command_index] == '-') {
        flag = extract_word();
        skip_whitespace();
    }
    pattern = extract_word();
    skip_whitespace();
    while (command_index < command.size()) {
        std::string file = extract_word();
        if (!file.empty()) {
            filenames.push_back(file);
        }
        skip_whitespace();
    }
    run();
}
