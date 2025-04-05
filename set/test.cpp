#include <iostream>
#include "set.hpp"

int main(){
    my::set<int> s1={7, 8, 10, 9, 7, 2, 0, 9, -1};
    my::set<int> s2={1, 8, 9, 6};
    s1.insert(5);
    s1.remove(5);
    s2=std::move(s1);
    for(auto& el : s1){
        std::cout<<el<<"  ";
    }
    std::cout<<std::endl;
    for(auto& el : s2){
        std::cout<<el<<"  ";
    }
    std::cout<<std::endl;
    return 0;
}