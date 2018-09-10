#include "TaoMath/Point.hpp"
#include "TaoMath/PointF.hpp"
#include <gtest/gtest.h>

using namespace TaoMath;
TEST(testPointF, test1)
{
    PointF p1;
    ASSERT_TRUE(p1.isNull());
    PointF p2(1, 2);
    ASSERT_TRUE(fuzzyCompare(p2.x(), 1));
    ASSERT_TRUE(fuzzyCompare(p2.y(), 2));

    PointF p3(p2);
    ASSERT_TRUE(fuzzyCompare(p3.x(), 1));
    ASSERT_TRUE(fuzzyCompare(p3.y(), 2));

    ASSERT_EQ(p3.manhattanLength(), 3);
    p3.rx()++;
    ASSERT_EQ(p3.x(), 2);
    p3.ry()++;
    ASSERT_EQ(p3.y(), 3);

    p3.setX(p3.x() + 1.1f);
    ASSERT_EQ(p3.x(), 3.1f);
    p3.setY(p3.y() + 1.3f);
    ASSERT_EQ(p3.y(), 4.3f);
}
TEST(testPointF, test2)
{
    PointF p1(10, 4);
    p1 += 3;
    ASSERT_TRUE(PointF(13, 7) == p1);
    p1 += 1.5;
    ASSERT_TRUE(PointF(14.5f, 8.5f) == p1);
    p1 += PointF(1, 2);
    ASSERT_TRUE(PointF(15.5f, 10.5f) == p1);

    p1 -= 3;
    ASSERT_TRUE(PointF(12.5f, 7.5f) == p1);
    p1 -= 2.1;
    ASSERT_TRUE(PointF(10.4f, 5.4f) == p1);

    p1 -= PointF(1, 2);

    ASSERT_TRUE(PointF(9.4f, 3.4f) == p1);

    p1 *= 2;
    ASSERT_EQ(PointF(18.8f, 6.8f), p1);
    p1 *= 0.1;
    ASSERT_EQ(PointF(1.88f, 0.68f), p1);

    p1 /= 0.5;
    ASSERT_EQ(PointF(3.76f, 1.36f), p1);

    p1 /= 2;
    ASSERT_EQ(PointF(1.88f, 0.68f), p1);

    p1 /= 0.0;
}
TEST(testPointF, test3)
{
    PointF p1(2, 2);
    PointF p2(3, 3);
    auto   p = PointF::dotProduct(p1, p2);
    ASSERT_EQ(p, 12);
}
TEST(testPointF, test4)
{
    PointF p1(2, 2);
    PointF p2(3, 3);
    PointF p3(3, 3);
    ASSERT_TRUE(p2 == p3);
    ASSERT_TRUE(p1 != p2);
    {
        auto p = p1 + p2;
        ASSERT_EQ(p1, PointF(2, 2));
        ASSERT_EQ(p, PointF(5, 5));
    }
    {
        auto p = p1 - p2;
        ASSERT_EQ(p, PointF(-1, -1));
    }
    {
        auto p = p1 * 3;
        ASSERT_EQ(p, PointF(6, 6));
    }
    {
        auto p = p1 * 2.5;
        ASSERT_EQ(p, PointF(5, 5));
    }
    {
        auto p = 3 * p1;
        ASSERT_EQ(p, PointF(6, 6));
    }
    {
        auto p = 2.5 * p1;
        ASSERT_EQ(p, PointF(5, 5));
    }
    {
        auto p = p1 / 2;
        ASSERT_EQ(p, PointF(1, 1));
    }
    {
        auto p = p1 / 0.5;
        ASSERT_EQ(p, PointF(4, 4));
    }
}
TEST(testPointF, test5)
{
    PointF pf(1.3f, 2.4f);
    auto   p = pf.toPoint();
    ASSERT_EQ(Point(1, 2), p);
}
