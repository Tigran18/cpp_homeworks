#include <iostream>
#include <chrono>
#include "vector.h"
#include <vector>

int main(){
    my::vector<int> integer_vec{7, 8, 9, 10};
    std::cout<<"Integer_vec elements are: ";
    for(std::size_t i=0; i<integer_vec.size(); i++){
        std::cout<<integer_vec[i]<<"   ";
    }
    std::cout<<"size is: "<<integer_vec.size()<<", capacity is: "<<integer_vec.capacity()<<std::endl;
    my::vector<int> new_vector;
    new_vector=std::move(integer_vec);
    std::cout<<"new_vector elements are: ";
    for(std::size_t i=0; i<new_vector.size(); i++){
        std::cout<<new_vector[i]<<"   ";
    }
    std::cout<<"size is: "<<new_vector.size()<<", capacity is: "<<new_vector.capacity()<<std::endl;
    std::cout<<"Integer_vec elements are: ";
    for(std::size_t i=0; i<integer_vec.size(); i++){
        std::cout<<integer_vec[i]<<"   ";
    }
    std::cout<<"size is: "<<integer_vec.size()<<", capacity is: "<<integer_vec.capacity()<<std::endl;
    return 0;
}