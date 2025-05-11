#include "set.hpp"

using namespace my;

template <typename T>
set<T>::node::node(const T& value, bool color):data(std::move(value)), color(color){
    color=red;
}

template <typename T>
bool set<T>::is_red(node* n)const{
    return n && n->color;
} 

template <typename T>
typename set<T>::node* set<T>::rotate_left(node* root){
    node* x=root->rightnode;
    root->rightnode=x->leftnode;
    x->leftnode=root;
    x->color=root->color;
    root->color=red;
    return x;
}

template <typename T>
typename set<T>::node* set<T>::rotate_right(node* root){
    node* x=root->leftnode;
    root->leftnode=x->rightnode;
    x->rightnode=root;
    x->color=root->color;
    root->color=red;
    return x;
}

template <typename T>
void set<T>::flip_colors(node* root){
    root->color=!root->color;
    if(root->leftnode){
        root->leftnode->color=!root->leftnode->color;
    }
    if(root->rightnode){
        root->rightnode->color=!root->rightnode->color;
    }
}

template <typename T>
typename set<T>::node* set<T>::insert(node* root, const T& value) {
    if (!root) {
        root = new node(value, red);
        ++size;
        return root;
    }
    if(value<root->data){
        root->leftnode=insert(root->leftnode, value);
    }
    else if(value>root->data){
        root->rightnode=insert(root->rightnode, value);
    }
    else{
        return root;
    }
    if(is_red(root->rightnode) && !is_red(root->leftnode)){
        root=rotate_left(root);
    }
    if(is_red(root->leftnode) && is_red(root->leftnode->leftnode)){
        root=rotate_right(root);
    }
    if(is_red(root->leftnode) && is_red(root->rightnode)){
        flip_colors(root);
    }
    return root;
}

template <typename T>
void set<T>::insert(const T& value){
    root=insert(root, value);
    root->color=black;
}

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
    delete n;
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
    return stack == other.stack;
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
typename set<T>::node* set<T>::delete_node(node* h, const T& value) {
    if (!h) return nullptr;
    if (value < h->data) {
        h->leftnode = delete_node(h->leftnode, value);
    } else if (value > h->data) {
        h->rightnode = delete_node(h->rightnode, value);
    } else {
        if (!h->leftnode) {
            node* temp = h->rightnode;
            delete h;
            --size;
            return temp;
        } else if (!h->rightnode) {
            node* temp = h->leftnode;
            delete h;
            --size;
            return temp;
        } else {
            node* min = find_min(h->rightnode);
            h->data = min->data;
            h->rightnode = delete_node(h->rightnode, min->data);
        }
    }
    if (is_red(h->rightnode) && !is_red(h->leftnode)) {
        h = rotate_left(h);
    }
    if (is_red(h->leftnode) && is_red(h->leftnode->leftnode)) {
        h = rotate_right(h);
    }
    if (is_red(h->leftnode) && is_red(h->rightnode)) {
        flip_colors(h);
    }
    return h;
}

template <typename T>
typename set<T>::node* set<T>::find_min(node* n) {
    while (n && n->leftnode) {
        n = n->leftnode;
    }
    return n;
}

template <typename T>
typename set<T>::iterator set<T>::find(const T& value) const {
    for(auto it=begin(); it!=end(); ++it){
        if(*it==value){
            return it;
        }
    }
    return 0;
}

template <typename T>
bool set<T>::contains(const T& value) const {
    node* current = root;
    while (current) {
        if (value < current->data)
            current = current->leftnode;
        else if (value > current->data)
            current = current->rightnode;
        else
            return true;
    }
    return false;
}
