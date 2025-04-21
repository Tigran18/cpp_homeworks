#include "vector.hpp"

using namespace my;

template <typename T>
void vector<T>::reallocate(std::size_t new_cap) {
    std::unique_lock<std::shared_mutex> lock(mutex);
    T* new_ptr = new T[new_cap];
    for (std::size_t i = 0; i < m_size; ++i) {
        new_ptr[i] = std::move(m_ptr[i]);
    }
    delete[] m_ptr;
    m_ptr = new_ptr;
    m_cap = new_cap;
}

template <typename T>
vector<T>::vector() : m_ptr(nullptr), m_size(0), m_cap(0) {}

template <typename T>
vector<T>::vector(std::initializer_list<T> args) : vector() {
    for (const T& arg : args) {
        push_back(arg);
    }
}

template <typename T>
vector<T>::vector(const vector& other) : m_ptr(new T[other.m_cap]), m_size(other.m_size), m_cap(other.m_cap) {
    for (std::size_t i = 0; i < m_size; ++i) {
        m_ptr[i] = other.m_ptr[i];
    }
}

template <typename T>
vector<T>::vector(vector&& other) noexcept : m_ptr(other.m_ptr), m_size(other.m_size), m_cap(other.m_cap) {
    other.m_ptr = nullptr;
    other.m_size = 0;
    other.m_cap = 0;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this != &other) {
        delete[] m_ptr;
        m_size = other.m_size;
        m_cap = other.m_cap;
        m_ptr = new T[m_cap];
        for (std::size_t i = 0; i < m_size; ++i) {
            m_ptr[i] = other.m_ptr[i];
        }
    }
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
    if (this != &other) {
        delete[] m_ptr;
        m_ptr = other.m_ptr;
        m_size = other.m_size;
        m_cap = other.m_cap;
        other.m_ptr = nullptr;
        other.m_size = 0;
        other.m_cap = 0;
    }
    return *this;
}

template <typename T>
void vector<T>::clear() {
    std::unique_lock<std::shared_mutex> lock(mutex);
    delete[] m_ptr;
    m_ptr = nullptr;
    m_size = 0;
    m_cap = 0;
}

template <typename T>
vector<T>::~vector() {
    clear();
}

template <typename T>
void vector<T>::push_back(const T& arg) {
    if (m_size == m_cap) {
        reallocate(m_cap == 0 ? 1 : 2 * m_cap);
    }
    m_ptr[m_size++] = arg;
}

template <typename T>
void vector<T>::push_back(T&& arg) {
    if (m_size == m_cap) {
        reallocate(m_cap == 0 ? 1 : 2 * m_cap);
    }
    m_ptr[m_size++] = std::move(arg);
}

template <typename T>
T& vector<T>::operator[](const std::size_t& k) {
    std::shared_lock<std::shared_mutex> lock(mutex);
    if (k >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_ptr[k];
}

template <typename T>
T& vector<T>::operator[](const std::size_t& k) const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    if (k >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return m_ptr[k];
}

template <typename T>
std::size_t vector<T>::size() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return m_size;
}

template <typename T>
std::size_t vector<T>::capacity() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return m_cap;
}

template <typename T>
T* vector<T>::begin() {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return m_ptr;
}

template <typename T>
T* vector<T>::end() {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return m_ptr + m_size;
}

template <typename T>
const T* vector<T>::begin() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return m_ptr;
}

template <typename T>
const T* vector<T>::end() const {
    std::shared_lock<std::shared_mutex> lock(mutex);
    return m_ptr + m_size;
}