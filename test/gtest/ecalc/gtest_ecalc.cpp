#include "gtest/gtest.h"
#include <iostream>
#include "ecalc.h"


TEST(gtest_ecalc, simple_test) {
    ecalc::calculate my_calc{"1 + 2"};
    EXPECT_DOUBLE_EQ(my_calc(), 3);
}

TEST(gtest_ecalc, simple_double_test) {
    ecalc::calculate my_calc{"1.1 + 2.2"};
    EXPECT_DOUBLE_EQ(my_calc(), 3.3);
}

TEST(gtest_ecalc, test_with_add_sub_nested_paranthesis) {
    ecalc::calculate my_calc{"( 5 + (2 + ( 3 - 1 - 6 + 20 + 4 ) + (4 - 2) + ( 6 + 7 ) ) - 2 )"};
    EXPECT_DOUBLE_EQ(my_calc(), 0);
}

TEST(gtest_ecalc, test_with_mul_div_nested_paranthesis) {
    ecalc::calculate my_calc{"( 5 * (2 * ( 3 / 1 * 6 * 20 / 4 )))"};
    EXPECT_DOUBLE_EQ(my_calc(), 900);
}

TEST(gtest_ecalc, complex_test) {
    ecalc::calculate my_calc{"( 5 + (2 + ( 3 ^ 1 * 6 + 2 ^ 4 / 4 ) + (4 * 2) * ( 6 + 7 ) ) - 2 )"};
    EXPECT_DOUBLE_EQ(my_calc(), 131);
}

TEST(gtest_ecalc, div_by_zero) {
    ecalc::calculate my_calc{"1 / 0"};
    EXPECT_DOUBLE_EQ(my_calc(), std::numeric_limits<double>::max());
}

// operators to be supported

// ^

// /
// *

// +
// -

// ()

// log
// ln
// sqrt
// round
// floor
// ceil

// pi