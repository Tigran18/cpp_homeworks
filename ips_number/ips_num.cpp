#include <iostream>
#include <set>
#include <string>
#include <fstream>

int main() {
    std::set<std::string> ips;
    std::string ip;
    std::ifstream file("ips_list.txt");
    if (!file) {
        std::cerr << "Error opening file!\n";
        return 1;
    }
    while (file >> ip) {
        ips.insert(ip);
    }
    file.close();
    std::cout << "Number of unique IPs: " << ips.size() << std::endl;
    return 0;
}