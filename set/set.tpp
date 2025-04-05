#include "set.hpp"

using namespace my;

template <typename T>
set<T>::node::node(const T& value):data(std::move(value)){}

template <typename T>
set<T>::set():root(nullptr), size(0){}

template <typename T>
template <typename ...Args>
set<T>::set(T value, Args ...args):set(){
    insert(value);
    (insert(args), ...);
}

template <typename T>
set<T>::set(const set& other):root(nullptr), size(0){
    for(auto it=other.begin(); it!=other.end(); ++it){
        insert(*it);
    }
}

template <typename T>
set<T>::set(set&& other)noexcept:root(other.root), size(other.size){
    other.root=nullptr;
    other.size=0;
}

template <typename T>
set<T>& set<T>::operator=(const set& other){
    if(this!=&other){
        delete_tree(root);
        root=nullptr;
        for(auto it=other.begin(); it!=other.end(); ++it){
            insert(*it);
        }
    }
    return *this;
}

template <typename T>
set<T>& set<T>::operator=(set&& other)noexcept{
    if(this!=&other){
        delete_tree(root);
        root=other.root;
        size=other.size;
        other.root=nullptr;
        other.size=0;
    }
    return *this;
}

template <typename T>
set<T>::~set(){
    delete_tree(root);
}

template <typename T>
void set<T>::delete_tree(node* n){
    if(!n){
        return;
    }
    delete_tree(n->leftnode);
    delete_tree(n->rightnode);
    --size;
    delete n;
}

template <typename T>
typename set<T>::node* set<T>::insert(const T& value) {
    if (!root) {
        root = new node(value);
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

template <typename T>
void set<T>::remove(const T& value) {
    root = delete_node(root, value);
}

template <typename T>
typename set<T>::node* set<T>::delete_node(node* n, const T& value) {
    if (!n) {
        return n;
    }
    if (value < n->data) {
        n->leftnode = delete_node(n->leftnode, value);
    }
    else if (value > n->data) {
        n->rightnode = delete_node(n->rightnode, value);
    }
    else {
        if (!n->leftnode && !n->rightnode) {
            delete n;
            return nullptr;
        }
        
        else if (!n->leftnode) {
            node* temp = n->rightnode;  
            delete n;  
            return temp;
        }
        else if (!n->rightnode) {
            node* temp = n->leftnode; 
            delete n;  
            return temp;  
        }
        else {
            node* successor = find_min(n->rightnode);

            n->data = successor->data;

            n->rightnode = delete_node(n->rightnode, successor->data);
        }
    }
    return n;
}

template <typename T>
typename set<T>::node* set<T>::find_min(node* n) {
    while (n && n->leftnode) {
        n = n->leftnode;
    }
    return n;
}
