#include "allocator.h"
#include <vector>
#include <iostream>

int main() {
    try {
        std::vector<int, SimpleAllocator<int>> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        std::cout << "Vector elements: ";
        for (int val : vec) {
            std::cout << val << " ";
        }
        std::cout << "\n";

        int* ptr = SimpleAllocator<int>::allocate(5);

        for (int i = 0; i < 5; ++i) {
            ptr[i] = i * 10;
        }

        std::cout << "Allocated values: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << ptr[i] << " ";
        }
        std::cout << "\n";

        SimpleAllocator<int>::deallocate(ptr, 5);
        std::cout << "Memory deallocated successfully.\n";

    } catch (const std::bad_alloc& e) {
        std::cerr << "Allocation failed: " << e.what() << "\n";
    }
    return 0;
}
