#include <iostream>
#include "set.hpp"

int main(){
    my::set<int> s1={7, 8, 10, 9, 7, 2, 0, 9, -1};
    for(auto& el : s1){
        std::cout<<el<<"  ";
    }
    std::cout<<std::endl;
    return 0;
}