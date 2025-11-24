#include <algorithm>

#include <array.h>

template<class T, class Alloc>
Array<T, Alloc>::Array() = default;

template<class T, class Alloc>
Array<T, Alloc>::Array(size_t size, const Alloc& a) : alloc(a) { resize(size); }

template<class T, class Alloc>
Array<T, Alloc>::Array(size_t size, const T& value, const Alloc& a) : alloc(a) {
    reserve(size);
    std::uninitialized_fill_n(v, size, value);
    sz = size;
}

template<class T, class Alloc>
Array<T, Alloc>::Array(const std::initializer_list<T>& lst, const Alloc& a) : alloc(a) {
    reserve(lst.size());
    std::copy(lst.begin(), lst.end(), v);
    sz = lst.size();
}

template<class T, class Alloc>
Array<T, Alloc>::Array(const Array& other) : alloc(traits::select_on_container_copy_construction(other.alloc)) {
    reserve(other.sz);
    std::copy(other.v, other.v + other.sz, v);
    sz = other.sz;
}

template<class T, class Alloc>
Array<T, Alloc>::Array(Array&& other) noexcept
: sz(other.sz), cap(other.cap), v(other.v), alloc(std::move(other.alloc)) {
    other.sz = 0;
    other.cap = 0;
    other.v = nullptr;
}

template<class T, class Alloc>
Array<T, Alloc>::~Array() {
    clear();
    if (v) traits::deallocate(alloc, v, cap);
}

template<class T, class Alloc>
void Array<T, Alloc>::resize(size_t new_size) {
    if (new_size > cap) reserve(new_size > cap * 2 ? new_size : cap * 2);
    for (size_t i = sz; i < new_size; ++i) { traits::construct(alloc, v + i); }
    for (size_t i = new_size; i < sz; ++i) { traits::destroy(alloc, v + i); }
    sz = new_size;
}

template<class T, class Alloc>
void Array<T, Alloc>::reserve(size_t new_cap) {
    if (new_cap <= cap) return;
    T* new_v = traits::allocate(alloc, new_cap);
    if (v) {
        std::move(v, v + sz, new_v);
        for (size_t i = 0; i < sz; ++i) { traits::destroy(alloc, v + i); }
        traits::deallocate(alloc, v, cap);
    }
    v = new_v;
    cap = new_cap;
}

template<class T, class Alloc>
void Array<T, Alloc>::push(const T& value) {
    if (sz >= cap) reserve(cap > 0 ? cap * 2 : 1);
    traits::construct(alloc, v + sz, value);
    ++sz;
}

template<class T, class Alloc>
void Array<T, Alloc>::pop() {
    if (sz > 0) traits::destroy(alloc, v + --sz);
}

template<class T, class Alloc>
void Array<T, Alloc>::erase(size_t ind) {
    if (ind >= sz) return;
    traits::destroy(alloc, v + ind);
    std::move(v + ind + 1, v + sz, v + ind);
    --sz;
}

template<class T, class Alloc>
void Array<T, Alloc>::clear() {
    for (size_t i = 0; i < sz; ++i) { traits::destroy(alloc, v + i); }
    sz = 0;
}

template<class T, class Alloc>
size_t Array<T, Alloc>::size() const { return sz; }

template<class T, class Alloc>
size_t Array<T, Alloc>::capacity() const { return cap; }

template<class T, class Alloc>
T& Array<T, Alloc>::operator[](size_t i) { return v[i]; }

template<class T, class Alloc>
const T& Array<T, Alloc>::operator[](size_t i) const { return v[i]; }

template<class T, class Alloc>
Array<T, Alloc>& Array<T, Alloc>::operator=(const Array& other) {
    if (this != &other) {
        clear();
        if (cap < other.sz) {
            if (v) traits::deallocate(alloc, v, cap);
            cap = other.sz;
            v = traits::allocate(alloc, cap);
        }
        std::uninitialized_copy(other.v, other.v + other.sz, v);
        sz = other.sz;
    }
    return *this;
}

template<class T, class Alloc>
Array<T, Alloc>& Array<T, Alloc>::operator=(Array&& other) noexcept {
    if (this != &other) {
        clear();
        if (v) traits::deallocate(alloc, v, cap);
        sz = other.sz;
        cap = other.cap;
        v = other.v;
        alloc.~Alloc();
        new (&alloc) Alloc(other.alloc);
        other.sz = 0;
        other.cap = 0;
        other.v = nullptr;
    }
    return *this;
}