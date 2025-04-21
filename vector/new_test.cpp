#include <iostream>
#include "vector.hpp"

int main(){
    my::vector<int> vec1{7, 8, 0, -1, 9, -10};
    for(auto el : vec1){
        std::cout<<el<<"  ";
    }
    std::cout<<std::endl;
    return 0;
}