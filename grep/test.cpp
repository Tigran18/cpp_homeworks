#include <iostream>
#include "grep.hpp"
#include <string>

int main() {
    std::string command;
    std::cout<<"grep something\n";
    while (true) {
        std::getline(std::cin, command);
        if (command.empty()) continue;
        std::string first_word;
        size_t i = 0;
        while (i < command.length() && command[i] != ' ') {
            first_word += command[i++];
        }
        if (first_word != "grep") {
            std::cout << "Command isn't grep\n";
        } else {
            std::cout << "Command is grep\n";
            grep obj(command);
            obj.run();
        }
    }

    return 0;
}
