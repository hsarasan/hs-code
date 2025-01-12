#include <gtest/gtest.h>

/* build command => 
g++ -std=c++17 -I C:\cppcode\code\googletest\googletest\include .\gtest_sample.cpp -lgtest -L.
*/

// Function to be tested
int Add(int a, int b) {
    return a + b;
}

// Test case 1: Test for correct addition
TEST(AdditionTest, PositiveNumbers) {
    EXPECT_EQ(Add(2, 3), 5);  // Test for 2 + 3 = 5
    EXPECT_EQ(Add(10, 20), 30); // Test for 10 + 20 = 30
}

// Test case 2: Test for edge case where one number is zero
TEST(AdditionTest, Zero) {
    EXPECT_EQ(Add(0, 5), 5);  // Test for 0 + 5 = 5
    EXPECT_EQ(Add(0, 0), 0);  // Test for 0 + 0 = 0
}

// Test case 3: Test for negative numbers
TEST(AdditionTest, NegativeNumbers) {
    EXPECT_EQ(Add(-2, -3), -5);  // Test for -2 + -3 = -5
    EXPECT_EQ(Add(-5, 5), 0);    // Test for -5 + 5 = 0
}

// Main function to run the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Initialize Google Test
    return RUN_ALL_TESTS();  // Run all the tests and return the result
}
