#pragma once
#include <initializer_list>
#include <algorithm>
#include <cstddef>

namespace my {
    template <typename T>
    class vector {
    private:
        T* m_ptr = nullptr;
        std::size_t m_size = 0;
        std::size_t m_cap = 0;

        void reallocate(std::size_t new_cap);

    public:
        vector();

        vector(std::initializer_list<T> args);

        vector(const vector& other);

        vector(vector&& other)noexcept;

        vector& operator=(const vector& other);

        vector& operator=(vector&& other)noexcept;

        ~vector();

        void clear();

        void push_back(const T& arg);

        T& operator[](const std::size_t& k);

        T& operator[](const std::size_t& k) const;

        std::size_t size() const;

        std::size_t capacity() const;

        T* begin();

        T* end();
        
        const T* begin()const;

        const T* end() const;
    };
}

#include "vector.tpp"