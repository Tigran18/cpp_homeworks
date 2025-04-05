#pragma once
#include "allocator.hpp"
#include <vector>
#include <cstdlib>
#include <algorithm>

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
    static void initialize(std::size_t newBlockSize, std::size_t newBlockCount) {
        if (pool) cleanup(); 
        pool = SimpleAllocator<char>::allocate(newBlockSize * newBlockCount);
        freeBlocks.clear();
        for (std::size_t i = 0; i < newBlockCount; ++i) {
            freeBlocks.push_back(pool + i * newBlockSize);
        }
        blockSize = newBlockSize;
        blockCount = newBlockCount;
    }

    [[nodiscard]] static void* allocate() {
        if (freeBlocks.empty()) {
            throw std::bad_alloc();
        }
        void* block = freeBlocks.back();
        freeBlocks.pop_back();
        return block;
    }

    static void deallocate(void* block) {
        char* charBlock = reinterpret_cast<char*>(block);
        if (std::find(freeBlocks.begin(), freeBlocks.end(), charBlock) != freeBlocks.end()) {
            throw std::runtime_error("Double free detected");
        }
        freeBlocks.push_back(charBlock);
    }

    static void cleanup() {
        if (pool) {
            SimpleAllocator<char>::deallocate(pool, blockSize * blockCount);
            pool = nullptr;
            freeBlocks.clear();
        }
    }
};

char* MemoryPool::pool = nullptr;
std::size_t MemoryPool::blockSize = 0;
std::size_t MemoryPool::blockCount = 0;
std::vector<char*> MemoryPool::freeBlocks;
