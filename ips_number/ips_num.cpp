#include <iostream>
#include <set>
#include <string>
#include <fstream>

int main() {
    std::set<std::string> ips;
    std::ifstream file("ips_list.txt");
    std::string ip;
    while (file >> ip) {
        ips.insert(ip);
    }
    file.close();
    std::cout << "Number of unique IPs: " << ips.size() << std::endl;
    return 0;
}