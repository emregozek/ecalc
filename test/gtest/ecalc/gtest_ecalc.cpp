#include "gtest/gtest.h"
#include <iostream>
#include "ecalc.h"

// TEST(gtest_ecalc, ctor) {
//     ecalc::calculate my_calc{"1 + 2"};
//     std::cout << my_calc;
// }

// TEST(gtest_ecalc, print) {
//     ecalc::calculate my_calc{"1 + 2"};
//     std::cout << my_calc;
// }

// TEST(gtest_ecalc, functor) {
//     ecalc::calculate my_calc{"1.1 + 2.2"};
//     auto d = my_calc();
//     EXPECT_DOUBLE_EQ(d, 3.3);
// }
TEST(gtest_ecalc, paranthesis_parsing) {
    ecalc::calculate my_calc{"(1 + 2) * (3 * (5 + 2))"};
    std::cout << my_calc << "\n";
    my_calc();
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