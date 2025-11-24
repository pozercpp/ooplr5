#pragma once

#include <algorithm>

#include <array.h>

template<class T>
Array<T>::Array() : sz(0), cap(1), v(new T[cap], deleter) {}

template<class T>
Array<T>::Array(size_t n) : sz(n), cap(n > 0 ? 4 * n : 1), v(new T[cap], deleter) {}

template<class T>
Array<T>::Array(size_t n, const T& elem) : sz(n), cap(n > 0 ? 4 * n : 1), v(new T[cap], deleter) {
    for (size_t i = 0; i < sz; ++i) {
        v[i] = elem;
    }
}

template<class T>
Array<T>::~Array() = default;

template<class T>
Array<T>::Array(const std::initializer_list<T>& lst) : sz(0), cap(1), v(new T[cap], deleter) {
    for (const T& elem : lst) { 
        push(elem); 
    }
}

template<class T>
Array<T>::Array(const Array& other) : sz(other.sz), cap(other.cap), v(new T[cap], deleter) {
    std::copy(other.v.get(), other.v.get() + sz, v.get());
}

template<class T>
Array<T>::Array(Array&& other) noexcept : sz(other.sz), cap(other.cap), v(std::move(other.v)) {
    other.sz = 0;
    other.cap = 0;
}

template<class T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        sz = other.sz;
        cap = other.cap;
        v = std::shared_ptr<T[]>(new T[cap], deleter);
        std::copy(other.v.get(), other.v.get() + sz, v.get());
    }
    return *this;
}

template<class T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        sz = other.sz;
        cap = other.cap;
        v = std::move(other.v);
        
        other.sz = 0;
        other.cap = 0;
    }
    return *this;
}

template<class T>
void Array<T>::resize(size_t newsize) {
    auto new_v = std::shared_ptr<T[]>(new T[newsize], deleter);
    std::copy(v.get(), v.get() + std::min(sz, newsize), new_v.get());
    v = new_v;
    cap = newsize;
    if (sz > newsize) {
        sz = newsize;
    }
}

template<class T>
void Array<T>::push(const T& elem) {
    if (sz >= cap) {
        resize(2 * cap);
    }
    v[sz++] = elem;
}

template<class T>
void Array<T>::pop() {
    if (sz) {
        --sz;
    }
}

template<class T>
void Array<T>::erase(size_t ind) {
    if (ind >= sz) return;
    for (size_t i = ind; i + 1 < sz; ++i) {
        v[i] = v[i + 1];
    }
    --sz;
}

template<class T>
void Array<T>::clear() { 
    sz = 0; 
}

template<class T>
T& Array<T>::operator[](size_t ind) { 
    return v[ind]; 
}

template<class T>
const T& Array<T>::operator[](size_t ind) const { 
    return v[ind]; 
}

template<class T>
size_t Array<T>::size() const { 
    return sz; 
}

template<class T>
size_t Array<T>::capacity() const { 
    return cap; 
}
