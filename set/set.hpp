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

                node(T& value):data(std::move(value)){}
            };
            node* root=nullptr;
            std::size_t size=0;
        public:
           
        class iterator {
            private:
                std::vector<node*> stack;
                void pushLeft(node* n) {
                    while (n) {
                        stack.push_back(n);
                        n = n->leftnode;
                    }
                }
    
            public:
                iterator(node* root) {
                    pushLeft(root);
                }
    
                iterator& operator++() {
                    if (stack.empty()) return *this;
    
                    node* n = stack.back();
                    stack.pop_back();
                    if (n->rightnode) {
                        pushLeft(n->rightnode);
                    }
    
                    return *this;
                }
    
                const T& operator*() const {
                    return stack.back()->data;
                }
    
                const T* operator->() const {
                    return &(stack.back()->data);
                }
    
                bool operator==(const iterator& other) const {
                    if (stack.empty() && other.stack.empty()) return true;
                    if (stack.empty() || other.stack.empty()) return false;
                    return stack.back() == other.stack.back();
                }
    
                bool operator!=(const iterator& other) const {
                    return !(*this == other);
                }
            };
    

            set();

            template <typename ...Args>
            set(T data, Args ...args);

            node* insert(const T& value);

            set(const set& other);

            set(set&& other)noexcept;

            set& operator=(const set& other);

            set& operator=(set&& other)noexcept;
            
            iterator begin() const {
                return iterator(root);
            }

            iterator end() const {
                return iterator(nullptr);
            }
    };
}

#include "set.tpp"