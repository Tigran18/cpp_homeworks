#include <iostream>
#include "json_parser.hpp"

int main(){
    std::string str="example.json";
    json_parser obj(str);
    obj.print();
    return 0;
}