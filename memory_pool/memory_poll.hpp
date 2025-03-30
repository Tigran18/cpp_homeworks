#pragma once
#include "allocator.hpp"
#include <vector>
#include <cstdlib>

class MemoryPool {
private:
    MemoryPool() = delete;

    MemoryPool(const MemoryPool&) = delete;

    MemoryPool& operator=(const MemoryPool&) = delete;
    
    MemoryPool(MemoryPool&&) = delete;
    
    MemoryPool& operator=(MemoryPool&&) = delete;

    static char* pool;
    static std::size_t blockSize;
    static std::size_t blockCount;
    static std::vector<char*> freeBlocks;

public:
    static void initialize(std::size_t blockSize, std::size_t blockCount) {
        if (!pool) {
            pool = SimpleAllocator<char>::allocate(blockSize * blockCount);
            for (std::size_t i = 0; i < blockCount; ++i) {
                freeBlocks.push_back(pool + i * blockSize);
            }
            MemoryPool::blockSize = blockSize;
            MemoryPool::blockCount = blockCount;
        }
    }

    static void* allocate() {
        if (freeBlocks.empty()) {
            throw std::bad_alloc();
        }
        void* block = freeBlocks.back();
        freeBlocks.pop_back();
        return block;
    }

    static void deallocate(void* block) {
        freeBlocks.push_back(static_cast<char*>(block));
    }

    static void cleanup() {
        if (pool) {
            SimpleAllocator<char>::deallocate(pool, blockSize * blockCount);
            pool = nullptr;
        }
    }
};

char* MemoryPool::pool = nullptr;
std::size_t MemoryPool::blockSize = 0;
std::size_t MemoryPool::blockCount = 0;
std::vector<char*> MemoryPool::freeBlocks;
