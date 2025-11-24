cmake_minimum_required(VERSION 3.14)
project(CustomArrayProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_library(allocator STATIC src/allocator.cpp)
target_include_directories(allocator PUBLIC include)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE allocator)

enable_testing()

add_executable(tests test/test.cpp src/allocator.cpp)
target_link_libraries(tests PRIVATE gtest_main gtest allocator)
target_include_directories(tests PRIVATE include)

add_test(NAME AllocatorAndArrayTests COMMAND tests)