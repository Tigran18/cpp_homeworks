#include <iostream>
#include "memory_poll.hpp"

int main() {
    MemoryPool::initialize(2, 10);

    int* ptr1 = static_cast<int*>(MemoryPool::allocate());
    int* ptr2 = static_cast<int*>(MemoryPool::allocate());
    *ptr1=21546210;
    *ptr2=16544321;
    std::cout << "Allocated: " << *ptr1<<" at address "<<reinterpret_cast<void*>(ptr1) << " and " << *ptr2<<" at address "<<reinterpret_cast<int*>(ptr2) << std::endl;

    MemoryPool::deallocate(ptr1);
    MemoryPool::deallocate(ptr2);
    std::cout << "Deallocated both pointers." << std::endl;

    MemoryPool::cleanup();

    return 0;
}
