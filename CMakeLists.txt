cmake_minimum_required(VERSION 3.10)
project(GeometryFigures VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

set(MAIN_SOURCE
    src/main.cpp
)

set(HEADERS
    include/array.ipp
    include/point.ipp
    include/figure.ipp
    include/five.ipp
    include/six.ipp
    include/eight.ipp
)

add_executable(geometry_figures ${MAIN_SOURCE})
target_include_directories(geometry_figures PRIVATE include)
target_compile_features(geometry_figures PRIVATE cxx_std_20)

set(TEST_SOURCES
    test/tests.cpp
    test/array_test.cpp
    test/figure_test.cpp
)

add_executable(array_tests test/array_test.cpp)
target_include_directories(array_tests PRIVATE include)
target_compile_features(array_tests PRIVATE cxx_std_20)
target_link_libraries(array_tests GTest::gtest GTest::gtest_main)

add_executable(figure_tests test/figure_test.cpp)
target_include_directories(figure_tests PRIVATE include)
target_compile_features(figure_tests PRIVATE cxx_std_20)
target_link_libraries(figure_tests GTest::gtest GTest::gtest_main)

add_executable(all_tests ${TEST_SOURCES})
target_include_directories(all_tests PRIVATE include)
target_compile_features(all_tests PRIVATE cxx_std_20)
target_link_libraries(all_tests GTest::gtest GTest::gtest_main)