#include <gtest/gtest.h>
#include "TaoMath/TaoMath"
using namespace TaoMath;
TEST(testPoint, test1) {
    Point p;
    ASSERT_TRUE(p.isNull());
}