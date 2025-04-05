#pragma once
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

namespace my{
    template <typename T>
    class set{
        private:
            struct node{
                T data;
                node* rightnode=nullptr;
                node* leftnode=nullptr;

                node(const T& value);
            };
            node* root=nullptr;
            std::size_t size=0;
            node* delete_node(node* n , const T& value);
            node* find_min(node* n);
        public:
            set();

            template <typename ...Args>
            set(T data, Args ...args);

            node* insert(const T& value);

            set(const set& other);

            set(set&& other)noexcept;

            set& operator=(const set& other);

            set& operator=(set&& other)noexcept;

            void remove(const T& value);

            ~set();

            void delete_tree(node* n);

        class iterator {
            private:
                std::vector<node*> stack;
                void pushLeft(node* n);
    
            public:
                iterator(node* root);
    
                iterator& operator++();
    
                const T& operator*() const;
    
                const T* operator->() const;
    
                bool operator==(const iterator& other) const;
    
                bool operator!=(const iterator& other) const;
            };
            
            iterator begin() const;

            iterator end() const;
    };
}

#include "set.tpp"