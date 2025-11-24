#include <gtest/gtest.h>
#include <array.h>

class ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_GE(arr.capacity(), 1);
}

TEST_F(ArrayTest, SizeConstructor) {
    Array<int> arr(5);
    EXPECT_EQ(arr.size(), 5);
}

TEST_F(ArrayTest, ValueConstructor) {
    Array<int> arr(3, 42);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 42);
    EXPECT_EQ(arr[1], 42);
    EXPECT_EQ(arr[2], 42);
}

TEST_F(ArrayTest, InitializerListConstructor) {
    Array<int> arr{1, 2, 3, 4, 5};
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[4], 5);
}

TEST_F(ArrayTest, PushAndSize) {
    Array<int> arr;
    arr.push(10);
    arr.push(20);
    arr.push(30);
    
    EXPECT_EQ(arr.size(), 3);
}

TEST_F(ArrayTest, PushAndAccess) {
    Array<int> arr;
    arr.push(10);
    arr.push(20);
    
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST_F(ArrayTest, Pop) {
    Array<int> arr{1, 2, 3};
    arr.pop();
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST_F(ArrayTest, PopEmpty) {
    Array<int> arr;
    EXPECT_NO_THROW(arr.pop());
    EXPECT_EQ(arr.size(), 0);
}

TEST_F(ArrayTest, Erase) {
    Array<int> arr{1, 2, 3, 4, 5};
    arr.erase(2); // Удаляем элемент с индексом 2 (значение 3)
    
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 5);
}

TEST_F(ArrayTest, Clear) {
    Array<int> arr{1, 2, 3, 4, 5};
    arr.clear();
    
    EXPECT_EQ(arr.size(), 0);
}

TEST_F(ArrayTest, CopyConstructor) {
    Array<int> original{1, 2, 3};
    Array<int> copy(original);
    
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);
}

TEST_F(ArrayTest, AssignmentOperator) {
    Array<int> original{1, 2, 3};
    Array<int> copy;
    copy = original;
    
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);
}

TEST_F(ArrayTest, MoveConstructor) {
    Array<int> original{1, 2, 3};
    Array<int> moved(std::move(original));
    
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);
}

TEST_F(ArrayTest, Resize) {
    Array<int> arr{1, 2, 3};
    arr.resize(5);
    
    EXPECT_GE(arr.capacity(), 5);
    EXPECT_EQ(arr.size(), 3);
}

TEST_F(ArrayTest, OutOfBoundsAccess) {
    Array<int> arr{1, 2, 3};
    EXPECT_NO_THROW(arr[0]);
    EXPECT_NO_THROW(arr[2]);
}

TEST_F(ArrayTest, CapacityGrowth) {
    Array<int> arr;
    size_t initial_capacity = arr.capacity();
    for (int i = 0; i < initial_capacity + 1; ++i) {
        arr.push(i);
    }
    
    EXPECT_GT(arr.capacity(), initial_capacity);
    EXPECT_EQ(arr.size(), initial_capacity + 1);
}