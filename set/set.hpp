#pragma once
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

namespace my{
    template <typename T>
    class set{
        private:
            std::vector<T> m_set;
        public:
            set();

            set(std::initializer_list<T> init);
            
            set(const set& other);

            set(set&& other)noexcept;

            set& operator=(const set& other);

            set& operator=(set&& other)noexcept;

            auto begin();
            
            auto begin()const;
            
            auto end();
            
            auto end()const;

            bool empty() const;

            auto find(const T& data)const;

            std::size_t size()const;

            void insert(const T& data);

            void erase(const T& data);

            friend bool check<>(const set<T>& obj, T el);      
    };
}

#include "set.tpp"