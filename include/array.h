#pragma once

#include <memory>
#include <initializer_list>
#include <cstddef>
#include <memory_resource>
#include <iterator>

#include <allocator.h>

template<class T, class Alloc = std::pmr::polymorphic_allocator<T>>
class Array {
    using traits = std::allocator_traits<Alloc>;
    size_t sz = 0;
    size_t cap = 0;
    T* v = nullptr;
    Alloc alloc;

public:
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

    private:
        pointer m_ptr;

    public:
        iterator(pointer ptr = nullptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }

        iterator& operator++() { ++m_ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        iterator& operator--() { --m_ptr; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

        iterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        iterator operator+(difference_type n) const { iterator tmp = *this; tmp += n; return tmp; }

        iterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
        iterator operator-(difference_type n) const { iterator tmp = *this; tmp -= n; return tmp; }

        difference_type operator-(const iterator& other) const { return m_ptr - other.m_ptr; }

        reference operator[](difference_type n) const { return *(m_ptr + n); }

        bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
        bool operator<(const iterator& other) const { return m_ptr < other.m_ptr; }
        bool operator>(const iterator& other) const { return other < *this; }
        bool operator<=(const iterator& other) const { return !(*this > other); }
        bool operator>=(const iterator& other) const { return !(*this < other); }
    };

    class const_iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

    private:
        pointer m_ptr;

    public:
        const_iterator(pointer ptr = nullptr) : m_ptr(ptr) {}
        const_iterator(const iterator& it) : m_ptr(it.m_ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }

        const_iterator& operator++() { ++m_ptr; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

        const_iterator& operator--() { --m_ptr; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

        const_iterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        const_iterator operator+(difference_type n) const { const_iterator tmp = *this; tmp += n; return tmp; }

        const_iterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
        const_iterator operator-(difference_type n) const { const_iterator tmp = *this; tmp -= n; return tmp; }

        difference_type operator-(const const_iterator& other) const { return m_ptr - other.m_ptr; }

        reference operator[](difference_type n) const { return *(m_ptr + n); }

        bool operator==(const const_iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }
        bool operator<(const const_iterator& other) const { return m_ptr < other.m_ptr; }
        bool operator>(const const_iterator& other) const { return other < *this; }
        bool operator<=(const const_iterator& other) const { return !(*this > other); }
        bool operator>=(const const_iterator& other) const { return !(*this < other); }
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Array();
    Array(size_t size, const Alloc& a = Alloc());
    Array(size_t size, const T& value, const Alloc& a = Alloc());
    Array(const std::initializer_list<T>& lst, const Alloc& a = Alloc());
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();

    void resize(size_t new_size);
    void reserve(size_t new_cap);
    void push(const T& value);
    void pop();
    void erase(size_t ind);
    void clear();

    size_t size() const;
    size_t capacity() const;

    T& operator[](size_t i);
    const T& operator[](size_t i) const;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    iterator begin() noexcept { return iterator(v); }
    iterator end() noexcept { return iterator(v + sz); }

    const_iterator begin() const noexcept { return const_iterator(v); }
    const_iterator end() const noexcept { return const_iterator(v + sz); }

    const_iterator cbegin() const noexcept { return const_iterator(v); }
    const_iterator cend() const noexcept { return const_iterator(v + sz); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
};

#include <array.ipp>