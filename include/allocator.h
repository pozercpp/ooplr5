#pragma once

#include <memory_resource>
#include <list>
#include <cstddef>
#include <algorithm>
#include <new>
#include <stdexcept>

class Allocator : public std::pmr::memory_resource {
public:
    Allocator(size_t);
    ~Allocator() noexcept;

    Allocator(const Allocator&) = delete;
    Allocator& operator=(const Allocator&) = delete;
    Allocator(Allocator&&) = delete;
    Allocator& operator=(Allocator&&) = delete;

private:
    void* do_allocate(size_t, size_t) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

    char* buffer = nullptr;
    size_t size = 0;
    std::list<std::pair<void*, size_t>> allocated_blocks;
};