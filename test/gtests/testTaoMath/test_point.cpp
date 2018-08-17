#include <gtest/gtest.h>
#include "TaoMath/Point.hpp"
using namespace TaoMath;
TEST(testPoint, test1) {
    Point p1;
    ASSERT_TRUE(p1.isNull());
    Point p2 (1, 2);
    ASSERT_TRUE (p2.x () == 1);
    ASSERT_TRUE (p2.y () == 2);

    Point p3 (p2);
    ASSERT_TRUE (p3.x () == 1);
    ASSERT_TRUE (p3.y () == 2);

    ASSERT_EQ (p3.manhattanLength (), 2);
    p3.rx ()++;
    ASSERT_EQ (p3.x (), 2);
    p3.ry ()++;
    ASSERT_EQ (p3.y (), 3);
}
TEST (testPoint, test2) {
    Point p1 (10, 4);
    p1 += 3;
    ASSERT_EQ (Point (13, 7), p1);
    p1 += 1.5;
    ASSERT_EQ (Point (15, 9), p1);
    p1 += Point (1, 2);
    ASSERT_EQ (Point (16, 11), p1);

    p1 -= 3;
    ASSERT_EQ (Point (13, 8), p1);
    p1 -= 2.1;
    ASSERT_EQ (Point (11, 6), p1);

    p1 -= Point (1, 2);
    ASSERT_EQ (Point (10, 4), p1);

    p1 *= 2;
    ASSERT_EQ (Point (20, 8), p1);
    p1 *= 0.1;
    ASSERT_EQ (Point (2, 1), p1);

    p1 /= 0.5;
    ASSERT_EQ (Point (4, 2), p1);

    p1 /= 2;
    ASSERT_EQ (Point (2, 1), p1);

    p1 /= 0.0;
}
TEST (testPoint, test3) {
    Point p1 (2, 2);
    Point p2 (3, 3);
    auto p = Point::dotProduct (p1, p2);
    ASSERT_EQ (p, 12);
}
TEST (testPoint, test4) {
    Point p1 (2, 2);
    Point p2 (3, 3);
    Point p3 (3, 3);
    ASSERT_TRUE (p2 == p3);
    ASSERT_TRUE (p1 != p2);
    {
        auto p = p1 + p2;
        ASSERT_EQ (p1, Point (2, 2));
        ASSERT_EQ (p, Point (5, 5));
    }
    {
        auto p = p1 - p2;
        ASSERT_EQ (p, Point (-1, -1));
    }
    {
        //auto p = p1 * 3;
        //ASSERT_EQ (p, Point (6, 6));
    }
}