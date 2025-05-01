#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <stdexcept>
#include <variant>

using JSONvalue = std::variant<std::string, int, bool>;

class JSON {
private:
    std::map<std::string, JSONvalue> elements;
    std::string content;
    size_t index = 0;

    void skip_whitespace() {
        while (index < content.size() && std::isspace(content[index])) {
            index++;
        }
    }

    std::string parse_string() {
        skip_whitespace();
        if (content[index] != '"') throw std::runtime_error("Expected '\"'");
        index++;    

        std::string result;
        while (index < content.size() && content[index] != '"') {
            result += content[index++];
        }

        if (index >= content.size() || content[index] != '"') {
            throw std::runtime_error("Unterminated string");
        }
        index++;
        return result;
    }

    JSONvalue parse_value() {
        skip_whitespace();

        if (content[index] == '"') {
            return parse_string();
        }

        if (content.compare(index, 4, "true") == 0) {
            index += 4;
            return true;
        }
        if (content.compare(index, 5, "false") == 0) {
            index += 5;
            return false;
        }

        if (content.compare(index, 4, "null") == 0) {
            index += 4;
            return std::string("null"); 
        }

        std::string result;
        if (content[index] == '-') {
            result += content[index++];
        }
        while (index < content.size() && std::isdigit(content[index])) {
            result += content[index++];
        }

        if (result.empty()) {
            throw std::runtime_error("Invalid value");
        }

        return std::stoi(result);
    }

    void parse() {
        skip_whitespace();
        if (content[index] != '{') throw std::runtime_error("Expected '{'");
        index++;

        while (true) {
            skip_whitespace();
            if (content[index] == '}') {
                index++;
                break;
            }

            std::string key = parse_string();
            skip_whitespace();

            if (content[index] != ':') throw std::runtime_error("Expected ':'");
            index++; 

            JSONvalue value = parse_value();
            elements[key] = value;

            skip_whitespace();
            if (content[index] == ',') {
                index++;
                continue;
            } else if (content[index] == '}') {
                index++;
                break;
            } else {
                throw std::runtime_error("Expected ',' or '}'");
            }
        }
    }

public:
    JSON(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Couldn't open the file\n";
            return;
        }

        char ch;
        while (file.get(ch)) {
            content += ch;
        }

        try {
            parse();
        } catch (const std::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << "\n";
        }
    }

    void print() const {
        for (const auto& [key, val] : elements) {
            std::cout << key << " -> ";

            if (std::holds_alternative<std::string>(val)) {
                std::cout << "[string] " << std::get<std::string>(val);
            }
            else if (std::holds_alternative<int>(val)) {
                std::cout << "[int] " << std::get<int>(val);
            }
            else if (std::holds_alternative<bool>(val)) {
                std::cout << "[bool] " << std::get<bool>(val);
            }

            std::cout << '\n';
        }
    }

    const std::map<std::string, JSONvalue>& get_elements() const {
        return elements;
    }
};
