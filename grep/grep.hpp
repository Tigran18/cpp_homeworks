#pragma once
#include <string>
#include <iostream>
#include <cctype>
#include <fstream>
#include <vector>

class grep {
private:
    std::string command;
    std::string pattern;
    std::vector<std::string> filenames;
    size_t command_index = 0;

    bool ignore_case = false;
    bool show_line_numbers = false;
    bool count_only = false;
    bool invert_match = false;
    bool list_filenames_only = false;
    bool suppress_filename = false;

    void skip_whitespace();
    std::string extract_word();
    std::string to_lower_str(const std::string& str);
    bool match_pattern(const std::string& line);
    void parse_flags();

public:
    grep(const std::string& cmd);
    grep(const grep& other) = delete;
    grep& operator=(const grep& other) = delete;
    grep(grep&& other) = delete;
    grep& operator=(grep&& other) = delete;

    void run();
};
