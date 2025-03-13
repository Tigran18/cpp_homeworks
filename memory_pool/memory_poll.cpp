#include <iostream>
#include <vector>

template <typename T>
struct SimpleAllocator {
    using value_type = T;

    SimpleAllocator() noexcept {}

    template <typename U>
    SimpleAllocator(const SimpleAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        if (n == 0) {
            return nullptr;
        }
        T* ptr = static_cast<T*>(::operator new(n * sizeof(T)));
        if (!ptr) {
            throw std::bad_alloc();
        }
        return ptr;
    }

    void deallocate(T* ptr, std::size_t n) noexcept {
        ::operator delete(ptr);
    }
};

class MemoryPool {
private:
    char* pool;
    std::size_t blockSize;
    std::size_t blockCount;
    std::vector<char*> freeBlocks;
    SimpleAllocator<char> allocator;

public:
    MemoryPool(std::size_t blockSize, std::size_t blockCount)
        : blockSize(blockSize), blockCount(blockCount) {
        allocator = SimpleAllocator<char>();
        pool = allocator.allocate(blockSize * blockCount);
        
        for (std::size_t i = 0; i < blockCount; ++i) {
            freeBlocks.push_back(pool + i * blockSize);
        }
    }

    ~MemoryPool() {
        allocator.deallocate(pool, blockSize * blockCount);
    }

    void* allocate() {
        if (freeBlocks.empty()) {
            throw std::bad_alloc();
        }
        void* block = freeBlocks.back();
        freeBlocks.pop_back();
        return block;
    }

    void deallocate(void* block) {
        freeBlocks.push_back(static_cast<char*>(block));
    }
};

int main() {
    MemoryPool pool(32, 10);

    void* ptr1 = pool.allocate();
    void* ptr2 = pool.allocate();
    std::cout << "Allocated: " << ptr1 << " and " << ptr2 << std::endl;

    pool.deallocate(ptr1);
    pool.deallocate(ptr2);
    std::cout << "Deallocated both pointers." << std::endl;
    
    return 0;
}
