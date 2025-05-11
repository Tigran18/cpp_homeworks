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
}
