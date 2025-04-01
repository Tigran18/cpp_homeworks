#include <iostream>
#include "memory_poll.hpp"

int main() {
    MemoryPool::initialize(32, 10);

    char* ptr1 = reinterpret_cast<char*>(MemoryPool::allocate());
    char* ptr2 = reinterpret_cast<char*>(MemoryPool::allocate());
    *ptr1='6';
    *ptr2=120;
    std::cout << "Allocated: " << *ptr1<<" at address "<<static_cast<void*>(ptr1) << " and " << *ptr2<<" at address "<<reinterpret_cast<int*>(ptr2) << std::endl;

    MemoryPool::deallocate(ptr1);
    MemoryPool::deallocate(ptr2);
    std::cout << "Deallocated both pointers." << std::endl;

    MemoryPool::cleanup();

    return 0;
}
