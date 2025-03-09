#include <iostream>
#include "allocator.h"

int main() {
    SimpleAllocator<int> alloc;

    int* p = alloc.allocate(10);
    for(int i=0; i<10; i++){
        *(p+i)=i*i;
    }
    for(int i=0; i<10; i++){
        std::cout<<*(p+i)<<std::endl;
    }
    alloc.deallocate(p, 5);
    return 0;
}