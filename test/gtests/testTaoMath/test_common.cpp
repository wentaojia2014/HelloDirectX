#include <TaoMath/TaoMath>
#include <gtest/gtest.h>
#include <iostream>
using std::cout;
using std::endl;

using namespace TaoMath;

TEST (testCommon, test1) {
    ASSERT_TRUE (isZero (0.0));
    ASSERT_TRUE (isZero (0.0f));
}
TEST (testCommon, test2) {
    ASSERT_TRUE (fuzzyCompare (0.1000001f, 0.1000002f));
    ASSERT_TRUE (fuzzyCompare (0.10000000000001, 0.10000000000002));
}

TEST (testCommon, test3) {
    auto degree = 37.;
    ASSERT_TRUE (fuzzyCompare (degree, radiansToDegrees (degreesToRadians (degree))));
}
TEST (testCommon, test4) {
    auto degree = 37.f;
    ASSERT_TRUE (fuzzyCompare (degree, radiansToDegrees (degreesToRadians (degree))));
}