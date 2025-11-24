#include <iostream>
#include <memory_resource>

#include<array.h>
#include<allocator.h>

int main() {
    Allocator pool(1024 * 1024);
    std::pmr::polymorphic_allocator<int> pmr_alloc(&pool);
    int n;
    std::cin >> n;
    Array<int, std::pmr::polymorphic_allocator<int>> arr(n, pmr_alloc);
    for (auto& i : arr) {
        std::cin >> i;
    }
    for (auto& i : arr) {
        std::cout << i << " ";
    }
    std::reverse(arr.begin(), arr.end());
    std::cout << std::endl;
    for (auto& i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::sort(arr.begin(), arr.end());
    for (auto& i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}