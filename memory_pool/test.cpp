#include <iostream>
<<<<<<< HEAD
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

=======
#include <vector>
#include "memory_poll.hpp"

int main() {
    MemoryPool pool(32, 10);

    void* ptr1 = pool.allocate();
    void* ptr2 = pool.allocate();
    std::cout << "Allocated: " << ptr1 << " and " << ptr2 << std::endl;

    pool.deallocate(ptr1);
    pool.deallocate(ptr2);
    std::cout << "Deallocated both pointers." << std::endl;
    
>>>>>>> refs/remotes/origin/main
    return 0;
}
