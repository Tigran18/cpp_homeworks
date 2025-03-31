#pragma once
#include <stdexcept>
#include <utility>

template <typename T>
class optional {
public:
    optional() : has_value_(false) {}

    optional(const T& value) : has_value_(true), value_(value) {}

    optional(T&& value) : has_value_(true), value_(std::move(value)) {}

    ~optional() {
        reset();
    }

    optional(const optional&) = delete;
    optional(optional&&) = delete;
    optional& operator=(const optional&) = delete;
    optional& operator=(optional&&) = delete;

    bool has_value() const {
        return has_value_;
    }

    T& value() {
        if (!has_value_) {
            throw std::runtime_error("Accessing value of an empty optional");
        }
        return value_;
    }

    const T& value() const {
        if (!has_value_) {
            throw std::runtime_error("Accessing value of an empty optional");
        }
        return value_;
    }

    T value_or(const T& default_value) const {
        return has_value_ ? value_ : default_value;
    }

    void reset() {
        has_value_ = false;
    }

    explicit operator bool() const {
        return has_value_;
    }

private:
    bool has_value_;
    T value_;
};