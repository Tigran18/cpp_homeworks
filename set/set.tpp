#include "set.hpp"

using namespace my;

template <typename T>
set<T>::set():root(nullptr), size(0){}

template <typename T>
template <typename ...Args>
set<T>::set(T value, Args ...args):set(){
    insert(value);
    (insert(args), ...);
}

template <typename T>
typename set<T>::node* set<T>::insert(const T& value) {
    if (!root) {
        root = new node(const_cast<T&>(value));
        ++size;
        return root;
    }

    node* current = root;
    while (true) {
        if (value == current->data) {
            return current;
        } else if (value < current->data) {
            if (!current->leftnode) {
                current->leftnode = new node(const_cast<T&>(value));
                ++size;
                return current->leftnode;
            }
            current = current->leftnode;
        } else {
            if (!current->rightnode) {
                current->rightnode = new node(const_cast<T&>(value));
                ++size;
                return current->rightnode;
            }
            current = current->rightnode;
        }
    }
}


template <typename T>
set<T>::set(const set& other)=default;

template <typename T>
set<T>::set(set&& other)noexcept{
}

template <typename T>
set<T>& set<T>::operator=(const set& other){
    if(this!=&other){
        
    }
    return *this;
}

template <typename T>
set<T>& set<T>::operator=(set&& other)noexcept{
    if(this!=&other){
    }
    return *this;
}
