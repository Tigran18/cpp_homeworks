#pragma once
#include <iostream>
#include <fstream>
#include <string>

class json_parser{
private:
    std::string file_name="";
    std::string str="";
public:
    json_parser(const std::string& file_name):file_name(file_name){
        std::ifstream file(file_name);
        char ch;
        while(file.get(ch)){
            str+=ch;
        };
    }

    void print()const{
        std::cout<<str<<std::endl;
    }
};