#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <fstream>

class grep {
private:
    size_t index = 0;
    std::string command;
    std::string flag;
    std::string pattern;
    std::string filename;

    void skip_whitespace() {
        while (index < command.size() && std::isspace(command[index])) {
            ++index;
        }
    }

    std::string extract_word() {
        std::string result;
        while (index < command.size() && !std::isspace(command[index])) {
            result += command[index++];
        }
        return result;
    }

    void run() {
        std::cout << "Flag: " << flag << "\n";
        std::cout << "Pattern: " << pattern << "\n";
        std::cout << "Filename: " << filename << "\n";
    }

public:
    grep(const std::string& cmd) : command(cmd) {
        index = 4;
        skip_whitespace();
        if (command[index] == '-') {
            flag = extract_word();
            skip_whitespace();
        }
        pattern = extract_word();
        skip_whitespace();
        filename = extract_word();
        run();
    }
};
