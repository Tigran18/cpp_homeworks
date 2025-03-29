#pragma once

#include <iostream>
#include <memory>

template <typename T>
struct SimpleAllocator {
    using value_type = T;

    SimpleAllocator()=delete;

    template <typename U>
    SimpleAllocator(const SimpleAllocator<U>&) noexcept {}

    [[nodiscard]] static T* allocate(std::size_t n) {
        if (n == 0) {
            return nullptr;
        }
        T* ptr = static_cast<T*>(::operator new(n * sizeof(T)));
        if (!ptr) {
            throw std::bad_alloc();
        }
        return ptr;
    }

    static void deallocate(T* ptr, std::size_t n) noexcept {
        ::operator delete(ptr);
    }
};
