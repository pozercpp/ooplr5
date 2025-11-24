#include <allocator.h>

Allocator::Allocator(size_t pool_size) : size(pool_size) {
    if (pool_size == 0) { throw std::invalid_argument("Pool size must be greater than zero"); }
    buffer = static_cast<char*>(::operator new(pool_size));
    if (!buffer) { throw std::bad_alloc(); }
}

Allocator::~Allocator() noexcept {
    allocated_blocks.clear();
    ::operator delete(buffer);
}

void* Allocator::do_allocate(size_t bytes, size_t alignment) {
    if (bytes == 0) { return nullptr; }
    char* start = buffer;
    char* end = buffer + size;
    for (auto it = allocated_blocks.begin(); it != allocated_blocks.end(); ++it) {
        auto cur = static_cast<char*>(it->first) - static_cast<char*>(start);
        if (cur >= static_cast<std::ptrdiff_t>(bytes)) {
            auto aligned_ptr = static_cast<void*>(start);
            auto space = static_cast<size_t>(cur);
            if (std::align(alignment, bytes, aligned_ptr, space)) {
                auto insert_it = allocated_blocks.begin();
                while (insert_it != allocated_blocks.end() && insert_it->first < aligned_ptr) { ++insert_it; }
                allocated_blocks.insert(insert_it, {aligned_ptr, bytes});
                return aligned_ptr;
            }
        }
        start = static_cast<char*>(it->first) + it->second;
    }
    auto cur = static_cast<char*>(end) - static_cast<char*>(start);
    if (cur >=  static_cast<ptrdiff_t>(bytes)) {
        auto aligned_ptr = static_cast<void*>(start);
        auto space = static_cast<size_t>(cur);
        if (std::align(alignment, bytes, aligned_ptr, space)) {
            auto insert_it = allocated_blocks.begin();
            while (insert_it != allocated_blocks.end() && insert_it->first < aligned_ptr) { ++insert_it; }
            allocated_blocks.insert(insert_it, {aligned_ptr, bytes});
            return aligned_ptr;
        }
    }
    throw std::bad_alloc();
}

void Allocator::do_deallocate(void* p, size_t bytes, size_t alignment) {
    if (p == nullptr) { return; }
    auto it = find(allocated_blocks.begin(), allocated_blocks.end(), std::make_pair(p, bytes));
    if (it != allocated_blocks.end()) { allocated_blocks.erase(it); }
}

bool Allocator::do_is_equal(const std::pmr::memory_resource& other) const noexcept { return this == &other; }