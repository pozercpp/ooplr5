#pragma once

#include<initializer_list>

template<class T> 
class Array {
    size_t sz, cap;
    std::shared_ptr<T[]> v;
    inline static auto deleter = [](T* ptr) {
        delete[] ptr;
    };

public:
    Array();
    Array(size_t);
    Array(size_t, const T&);
    Array(const std::initializer_list<T>&);
    Array(const Array&);
    Array(Array&&) noexcept;
    ~Array();

    void resize(size_t);
    void push(const T&);
    void pop();
    void erase(size_t);
    void clear();
    
    size_t size() const;
    size_t capacity() const;
    T& operator[](size_t);
    const T& operator[](size_t) const;
    Array& operator=(const Array&);
    Array& operator=(Array&&) noexcept;
};

#include <array.ipp>