#pragma once
#include "allocator.hpp"

class MemoryPool {
    private:
        char* pool;
        std::size_t blockSize;
        std::size_t blockCount;
        std::vector<char*> freeBlocks;
        
    public:
        MemoryPool(std::size_t blockSize, std::size_t blockCount)
            : blockSize(blockSize), blockCount(blockCount) {
            pool = SimpleAllocator<char>::allocate(blockSize * blockCount);
            
            for (std::size_t i = 0; i < blockCount; ++i) {
                freeBlocks.push_back(pool + i * blockSize);
            }
        }
    
        ~MemoryPool() {
            SimpleAllocator<char>::deallocate(pool, blockSize * blockCount);
            pool=nullptr;
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
    