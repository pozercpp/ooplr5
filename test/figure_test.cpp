#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include <sstream>

#include <point.h>
#include <figure.h>
#include <five.h>
#include <six.h>
#include <eight.h>

class PointTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PointTest, DefaultConstructor) {
    Point<double> p;
    EXPECT_DOUBLE_EQ(p.x, 0.0);
    EXPECT_DOUBLE_EQ(p.y, 0.0);
}

TEST_F(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 2.1);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 2.1);
}

TEST_F(PointTest, EqualityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.0, 3.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST_F(PointTest, InequalityOperator) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 3.0);
    
    EXPECT_TRUE(p1 != p2);
    EXPECT_FALSE(p1 != p1);
}

TEST_F(PointTest, StreamOutput) {
    Point<double> p(1.5, 2.5);
    std::ostringstream oss;
    oss << p;
    
    std::string output = oss.str();
    EXPECT_TRUE(output.find("1.5") != std::string::npos);
    EXPECT_TRUE(output.find("2.5") != std::string::npos);
}

TEST_F(PointTest, StreamInput) {
    Point<double> p;
    std::istringstream iss("3.14 2.71");
    iss >> p;
    
    EXPECT_DOUBLE_EQ(p.x, 3.14);
    EXPECT_DOUBLE_EQ(p.y, 2.71);
}

class FigureTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FigureTest, FiveDefaultConstructor) {
    Five<double> five;
    EXPECT_NO_THROW(five.Area());
    EXPECT_NO_THROW(five.Centr());
}


TEST_F(FigureTest, FiveCenterCalculation) {
    Five<double> five;
    Point<double> center = five.Centr();
    
    EXPECT_FALSE(std::isnan(center.x));
    EXPECT_FALSE(std::isnan(center.y));
    EXPECT_FALSE(std::isinf(center.x));
    EXPECT_FALSE(std::isinf(center.y));
}

TEST_F(FigureTest, SixDefaultConstructor) {
    Six<double> six;
    EXPECT_NO_THROW(six.Area());
    EXPECT_NO_THROW(six.Centr());
}

TEST_F(FigureTest, FigureEquality) {
    Five<double> five1({Point<double>(0,0), Point<double>(1,0), 
                       Point<double>(1,1), Point<double>(0,1), Point<double>(0.5,1.5)});
    Five<double> five2({Point<double>(0,0), Point<double>(1,0), 
                       Point<double>(1,1), Point<double>(0,1), Point<double>(0.5,1.5)});
    
    EXPECT_TRUE(five1 == five2);
}

TEST_F(FigureTest, FigureInequality) {
    Five<double> five1({Point<double>(0,0), Point<double>(1,0), 
                       Point<double>(1,1), Point<double>(0,1), Point<double>(0.5,1.5)});
    Five<double> five2({Point<double>(0,0), Point<double>(2,0), 
                       Point<double>(2,2), Point<double>(0,2), Point<double>(1,3)});
    
    EXPECT_TRUE(five1 != five2);
}

TEST_F(FigureTest, StreamOutputOperator) {
    Five<double> five;
    std::ostringstream oss;
    oss << five;
    std::string output = oss.str();
    
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find('(') != std::string::npos);
}