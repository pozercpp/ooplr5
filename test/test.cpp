#include <gtest/gtest.h>
#include <memory_resource>
#include <vector>
#include <numeric>
#include <cstring>

#include <allocator.h>
#include <array.h>

TEST(Allocator, BasicAllocationAndDeallocation) {
    Allocator pool(1024);
    void* p1 = pool.allocate(100, 8);
    void* p2 = pool.allocate(200, 16);
    EXPECT_NE(p1, nullptr);
    EXPECT_NE(p2, nullptr);
    EXPECT_GE(reinterpret_cast<char*>(p2) - reinterpret_cast<char*>(p1), 100);
    pool.deallocate(p1, 100, 8);
    pool.deallocate(p2, 200, 16);
}

TEST(Allocator, ReuseAfterDeallocate) {
    Allocator pool(1024);
    void* p1 = pool.allocate(128, 8);
    pool.deallocate(p1, 128, 8);
    void* p2 = pool.allocate(64, 8);
    EXPECT_EQ(p1, p2);
}

TEST(Allocator, MergingAdjacentBlocks) {
    Allocator pool(1024);
    void* a = pool.allocate(100, 8);
    void* b = pool.allocate(100, 8);
    void* c = pool.allocate(100, 8);
    pool.deallocate(b, 100, 8);
    pool.deallocate(a, 100, 8);
    void* big = pool.allocate(190, 8);
    EXPECT_EQ(a, big);
}

TEST(Allocator, AlignmentRespected) {
    Allocator pool(4096);

    void* p16 = pool.allocate(10, 16);
    void* p32 = pool.allocate(10, 32);
    void* p64 = pool.allocate(10, 64);

    EXPECT_EQ(reinterpret_cast<uintptr_t>(p16) % 16, 0u);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(p32) % 32, 0u);
    EXPECT_EQ(reinterpret_cast<uintptr_t>(p64) % 64, 0u);
}

TEST(PMRArray, DefaultConstructor) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> arr(0, alloc);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
}

TEST(PMRArray, ConstructorWithSizeAndValue) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> arr(10, 42, alloc);
    EXPECT_EQ(arr.size(), 10);
    EXPECT_TRUE(std::all_of(arr.begin(), arr.end(), [](int x) { return x == 42; }));
}

TEST(PMRArray, PushBackAndGrowth) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> arr(0, alloc);
    for (int i = 0; i < 1000; ++i) {
        arr.push(i);
    }
    EXPECT_EQ(arr.size(), 1000);
    EXPECT_EQ(arr[500], 500);
}

TEST(PMRArray, PopBack) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> arr({1, 2, 3, 4, 5}, alloc);
    arr.pop();
    arr.pop();
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[2], 3);
}

TEST(PMRArray, ResizeLarger) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);

    Array<int, std::pmr::polymorphic_allocator<int>> arr(5, 10, alloc);
    arr.resize(15);
    EXPECT_EQ(arr.size(), 15);
    EXPECT_EQ(arr[4], 10);
    EXPECT_EQ(arr[10], 0);
}

TEST(PMRArray, ResizeSmaller) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> arr({1, 2, 3, 4, 5}, alloc);
    arr.resize(2);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 2);
}

TEST(PMRArray, CopyConstructorAndAssignment) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> src({10, 20, 30}, alloc);
    Array<int, std::pmr::polymorphic_allocator<int>> copy(src);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[1], 20);
    Array<int, std::pmr::polymorphic_allocator<int>> assigned(0, alloc);
    assigned = src;
    EXPECT_EQ(assigned.size(), 3);
    EXPECT_EQ(assigned[2], 30);
}

TEST(PMRArray, MoveConstructorAndAssignment) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> src({1, 2, 3, 4}, alloc);
    size_t old_cap = src.capacity();
    Array<int, std::pmr::polymorphic_allocator<int>> moved(std::move(src));
    EXPECT_EQ(moved.size(), 4);
    EXPECT_EQ(src.size(), 0);
    EXPECT_EQ(src.capacity(), 0);
    Array<int, std::pmr::polymorphic_allocator<int>> assigned(0, alloc);
    assigned = std::move(moved);
    EXPECT_EQ(assigned.size(), 4);
    EXPECT_EQ(assigned.capacity(), old_cap);
}

TEST(PMRArray, IteratorAndRangeFor) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> arr({10, 20, 30, 40}, alloc);
    std::vector<int> check;
    for (int x : arr) check.push_back(x);
    EXPECT_EQ(check, std::vector<int>({10, 20, 30, 40}));
}

TEST(PMRArray, Clear) {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> alloc(&pool);
    Array<int, std::pmr::polymorphic_allocator<int>> arr(100, 999, alloc);
    arr.clear();
    EXPECT_EQ(arr.size(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}