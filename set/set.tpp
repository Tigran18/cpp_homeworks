#pragma once

namespace my {

template <typename T>
bool set<T>::is_red(node* n) const {
    return n && n->color == RED;
}

template <typename T>
typename set<T>::node* set<T>::rotate_left(node* h) {
    node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

template <typename T>
typename set<T>::node* set<T>::rotate_right(node* h) {
    node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

template <typename T>
void set<T>::flip_colors(node* h) {
    h->color = !h->color;
    if (h->left) h->left->color = !h->left->color;
    if (h->right) h->right->color = !h->right->color;
}

template <typename T>
set<T>::set() : root(nullptr), size(0) {}

template <typename T>
template <typename... Args>
set<T>::set(T value, Args... args) : set() {
    insert(value);
    (insert(args), ...);
}

template <typename T>
set<T>::set(const set& other) : root(nullptr), size(0) {
    for (auto it = other.begin(); it != other.end(); ++it)
        insert(*it);
}

template <typename T>
set<T>::set(set&& other) noexcept : root(other.root), size(other.size) {
    other.root = nullptr;
    other.size = 0;
}

template <typename T>
set<T>& set<T>::operator=(const set& other) {
    if (this != &other) {
        delete_tree(root);
        root = nullptr;
        size = 0;
        for (auto it = other.begin(); it != other.end(); ++it)
            insert(*it);
    }
    return *this;
}

template <typename T>
set<T>& set<T>::operator=(set&& other) noexcept {
    if (this != &other) {
        delete_tree(root);
        root = other.root;
        size = other.size;
        other.root = nullptr;
        other.size = 0;
    }
    return *this;
}

template <typename T>
set<T>::~set() {
    delete_tree(root);
    root = nullptr;
}

template <typename T>
void set<T>::delete_tree(node* h) {
    if (!h) return;
    delete_tree(h->left);
    delete_tree(h->right);
    delete h;
    --size;
}

template <typename T>
void set<T>::insert(const T& value) {
    root = insert(root, value);
    root->color = BLACK;
}

template <typename T>
typename set<T>::node* set<T>::insert(node* h, const T& value) {
    if (!h) {
        ++size;
        return new node(value, RED);
    }

    if (value < h->data)
        h->left = insert(h->left, value);
    else if (value > h->data)
        h->right = insert(h->right, value);
    else
        return h;

    if (is_red(h->right) && !is_red(h->left))
        h = rotate_left(h);
    if (is_red(h->left) && is_red(h->left->left))
        h = rotate_right(h);
    if (is_red(h->left) && is_red(h->right))
        flip_colors(h);

    return h;
}

template <typename T>
void set<T>::remove(const T& value) {
    root = delete_node(root, value);
    if (root) root->color = BLACK;
}

template <typename T>
typename set<T>::node* set<T>::delete_node(node* h, const T& value) {
    if (!h) return nullptr;

    if (value < h->data)
        h->left = delete_node(h->left, value);
    else if (value > h->data)
        h->right = delete_node(h->right, value);
    else {
        if (!h->left && !h->right) {
            delete h;
            --size;
            return nullptr;
        } else if (!h->left) {
            node* temp = h->right;
            delete h;
            --size;
            return temp;
        } else if (!h->right) {
            node* temp = h->left;
            delete h;
            --size;
            return temp;
        } else {
            node* successor = find_min(h->right);
            h->data = successor->data;
            h->right = delete_node(h->right, successor->data);
        }
    }
    return h;
}

template <typename T>
typename set<T>::node* set<T>::find_min(node* h) {
    while (h && h->left)
        h = h->left;
    return h;
}

template <typename T>
set<T>::iterator::iterator(node* root) {
    pushLeft(root);
}

template <typename T>
void set<T>::iterator::pushLeft(node* h) {
    while (h) {
        stack.push_back(h);
        h = h->left;
    }
}

template <typename T>
typename set<T>::iterator& set<T>::iterator::operator++() {
    if (stack.empty()) return *this;
    node* h = stack.back();
    stack.pop_back();
    if (h->right) pushLeft(h->right);
    return *this;
}

template <typename T>
const T& set<T>::iterator::operator*() const {
    return stack.back()->data;
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

}
