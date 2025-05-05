#include "json_parser.hpp"

void JSON::skip_whitespace() {
    while (index < content.size() && std::isspace(content[index])) {
        index++;
    }
}

std::string JSON::parse_string() {
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

JSON JSON::parse_object() {
    if (content[index] != '{') throw std::runtime_error("Expected '{'");
    size_t start_index = index;
    JSON nested(content, start_index);
    nested.parse();
    index = nested.index;
    return nested;
}

std::vector<JSONvalues_for_vector> JSON::parse_array() {
    std::vector<JSONvalues_for_vector> arr;
    index++;
    skip_whitespace();
    while (index < content.size() && content[index] != ']') {
        skip_whitespace();
        if (content[index] == '{') {
            arr.push_back(parse_object());
        } else if (content[index] == '"') {
            arr.push_back(parse_string());
        } else if (std::isdigit(content[index]) || content[index] == '-') {
            std::string num;
            if (content[index] == '-') num += content[index++];
            while (index < content.size() && std::isdigit(content[index])) {
                num += content[index++];
            }
            arr.push_back(std::stoi(num));
        } else if (content.compare(index, 4, "true") == 0) {
            index += 4;
            arr.push_back(true);
        } else if (content.compare(index, 5, "false") == 0) {
            index += 5;
            arr.push_back(false);
        } else {
            throw std::runtime_error("Invalid value in array");
        }
        skip_whitespace();
        if (content[index] == ',') {
            index++;
        } else if (content[index] != ']') {
            throw std::runtime_error("Expected ',' or ']'");
        }
        skip_whitespace();
    }
    if (content[index] != ']') {
        throw std::runtime_error("Expected ']'");
    }
    index++;
    return arr;
}

JSONvalue JSON::parse_value() {
    skip_whitespace();
    if (content[index] == '{') return parse_object();
    if (content[index] == '[') return parse_array();
    if (content[index] == '"') return parse_string();
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

void JSON::parse() {
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
        } else if (content[index] == '}') {
            index++;
            break;
        } else {
            throw std::runtime_error("Expected ',' or '}'");
        }
    }
}

void JSON::print_value(const JSONvalue& val, int tab) const {
    if (std::holds_alternative<std::string>(val)) {
        std::cout << "\"" << std::get<std::string>(val) << "\"";
    } else if (std::holds_alternative<int>(val)) {
        std::cout << std::get<int>(val);
    } else if (std::holds_alternative<bool>(val)) {
        std::cout << (std::get<bool>(val) ? "true" : "false");
    } else if (std::holds_alternative<JSON>(val)) {
        std::cout << "{\n";
        std::get<JSON>(val).print(tab + 2);
        std::cout << std::string(tab, ' ') << "}";
    } else if (std::holds_alternative<std::vector<JSONvalues_for_vector>>(val)) {
        std::cout << "[\n";
        const auto& vec = std::get<std::vector<JSONvalues_for_vector>>(val);
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << std::string(tab + 2, ' ');
            std::visit([&](auto&& arg) {
                if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                    std::cout << "\"" << arg << "\"";
                } else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, bool>) {
                    std::cout << (arg ? "true" : "false");
                } else {
                    std::cout << arg;
                }
            }, vec[i]);
            if (i + 1 < vec.size()) std::cout << ",";
            std::cout << "\n";
        }
        std::cout << std::string(tab, ' ') << "]";
    }
}

JSON::JSON(const std::string& filename) {
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

JSON::JSON(const std::string& raw_content, bool isRawString) : content(raw_content), index(0) {
    if (isRawString) {
        try {
            parse();
        } catch (const std::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << "\n";
        }
    }
}

void JSON::print(int tab = 2) const {
    std::cout << "{\n";
    auto it = elements.begin();
    while (it != elements.end()) {
        const auto& [key, val] = *it;
        std::cout << std::string(tab, ' ') << "\"" << key << "\": ";
        print_value(val, tab);
        ++it;
        if (it != elements.end()) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << "}\n";
}

void JSON::add(const std::string& key, const JSONvalue& val){
    elements[key]=val;
}

const JSONvalue& JSON::operator[](const std::string& key) const {
    return elements.at(key);    
}

std::ostream& operator<<(std::ostream& os, const JSONvalue& val) {
    std::visit([&os](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::string>) {
            os << "\"" << arg << "\"";
        } else if constexpr (std::is_same_v<T, bool>) {
            os << (arg ? "true" : "false");
        } else if constexpr (std::is_same_v<T, JSON>) {
            os << arg;
        } else if constexpr (std::is_same_v<T, std::vector<JSONvalues_for_vector>>) {
            os << "[";
            for (size_t i = 0; i < arg.size(); ++i) {
                std::visit([&os](auto&& innerVal) {
                    using InnerT = std::decay_t<decltype(innerVal)>;
                    if constexpr (std::is_same_v<InnerT, std::string>) {
                        os << "\"" << innerVal << "\"";
                    } else if constexpr (std::is_same_v<InnerT, bool>) {
                        os << (innerVal ? "true" : "false");
                    } else {
                        os << innerVal;
                    }
                }, arg[i]);
                if (i + 1 < arg.size()) os << ", ";
            }
            os << "]";
        } else {
            os << arg;
        }
    }, val);
    return os;
}


std::ostream& operator<<(std::ostream& os, const JSON& json) {
    os << "{ ";
    bool first = true;
    for (const auto& [key, value] : json.elements) {
        if (!first) os << ", ";
        first = false;
        os << "\"" << key << "\": " << value;
    }
    os << " }";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<JSONvalues_for_vector>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::visit([&os](auto&& arg) {
            os << arg;
        }, vec[i]);

        if (i + 1 < vec.size()) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
