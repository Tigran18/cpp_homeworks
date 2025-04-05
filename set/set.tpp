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
set<T>::iterator::iterator(node* root) {
    pushLeft(root);
}

template <typename T>
void set<T>::iterator::pushLeft(node* n) {
    while (n) {
        stack.push_back(n);
        n = n->leftnode;
    }
}

template <typename T>
typename set<T>::iterator& set<T>::iterator::operator++() {
    if (stack.empty()) return *this;

    node* n = stack.back();
    stack.pop_back();
    if (n->rightnode) {
        pushLeft(n->rightnode);
    }

    return *this;
}

template <typename T>
const T& set<T>::iterator::operator*() const {
    return stack.back()->data;
}

template <typename T>
const T* set<T>::iterator::operator->() const {
    return &(stack.back()->data);
}

template <typename T>
bool set<T>::iterator::operator==(const iterator& other) const {
    if (stack.empty() && other.stack.empty()) return true;
    if (stack.empty() || other.stack.empty()) return false;
    return stack.back() == other.stack.back();
}

template <typename T>
bool set<T>::iterator::operator!=(const iterator& other) const {
    return !(*this == other);
}

template <typename T>
typename set<T>::iterator set<T>::begin() const {
    return iterator(root);
}

template <typename T>
typename set<T>::iterator set<T>::end() const {
    return iterator(nullptr);
}