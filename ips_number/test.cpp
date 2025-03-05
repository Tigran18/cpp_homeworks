#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("ips_list.txt");  // Open the file
    if (!file) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {  // Read file line by line
        std::cout << line << std::endl;
    }

    file.close();  // Close the file
    return 0;
}
