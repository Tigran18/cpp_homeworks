#include <iostream>
#include "memory_poll.hpp"

int main() {
    MemoryPool::initialize(32, 10);

    void* ptr1 = MemoryPool::allocate();
    void* ptr2 = MemoryPool::allocate();
    std::cout << "Allocated: " << ptr1 << " and " << ptr2 << std::endl;

    MemoryPool::deallocate(ptr1);
    MemoryPool::deallocate(ptr2);
    std::cout << "Deallocated both pointers." << std::endl;

    MemoryPool::cleanup();

    return 0;
}
