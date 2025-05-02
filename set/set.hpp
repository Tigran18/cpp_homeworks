#pragma once
#include <vector>
#include <cstddef>

namespace my {
    template <typename T>
    class set {
    private:
        static constexpr bool RED = true;
        static constexpr bool BLACK = false;

        struct node {
            T data;
            node* left = nullptr;
            node* right = nullptr;
            bool color;
            node(const T& value, bool c = RED) : data(value), color(c) {}
        };

        node* root = nullptr;
        std::size_t size = 0;

        bool is_red(node* n) const;
        node* rotate_left(node* h);
        node* rotate_right(node* h);
        void flip_colors(node* h);
        node* insert(node* h, const T& value);
        node* delete_node(node* h, const T& value);
        node* find_min(node* h);
        void delete_tree(node* h);

    public:
        set();
        template <typename... Args>
        set(T first, Args... rest);
        set(const set& other);
        set(set&& other) noexcept;
        set& operator=(const set& other);
        set& operator=(set&& other) noexcept;
        ~set();

        void insert(const T& value);
        void remove(const T& value);

        class iterator {
        private:
            std::vector<node*> stack;
            void pushLeft(node* n);
        public:
            iterator(node* root);
            iterator& operator++();
            const T& operator*() const;
            bool operator!=(const iterator& other) const;
            bool operator==(const iterator& other) const;
        };

        iterator begin() const;
        iterator end() const;
    };
}

#include "set.tpp"
