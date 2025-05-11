#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <fstream>
#include <vector>

class grep {
private:
    size_t command_index = 0;
    std::string command;
    std::string flag;
    std::string pattern;
    std::vector<std::string> filenames;

    void skip_whitespace();

    std::string extract_word();
public:
    grep(const std::string& cmd);

    grep(const grep& other)=delete;

    grep& operator=(const grep& other)=delete;

    grep(grep&& other)=delete;

    grep& operator=(grep&& other)=delete;

    void run();
};
