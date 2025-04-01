#include <iostream>
#include "set.hpp"

int main(){
    my::set<int> s1={7, 8, 10, 9, 7, 2, 0, 9, -1};
    my::set<int> s2;
    s2=std::move(s1);
    std::cout<<"Printing s2 elements: ";
    for(auto& el : s2){
        std::cout<<el<<"  ";
    }
    std::cout<<std::endl;
    std::cout<<"Printing s1 elements after move assignement: ";
    for(auto& el : s1){
        std::cout<<el<<"  ";
    }
    std::cout<<"Finding the iterator of number 9 in s2: "<<*s2.find(9);
    std::cout<<"Inserting 5: "<<std::endl;
    s2.insert(5);
    std::cout<<"Printing s1 elements after inserting 5: ";
    for(auto& el : s2){
        std::cout<<el<<"  ";
    }
    std::cout<<"Erasing 5: "<<std::endl;
    s2.erase(5);
    std::cout<<"Printing s1 elements after inserting 5: ";
    for(auto& el : s2){
        std::cout<<el<<"  ";
    }
    std::cout<<std::endl;
    return 0;
}