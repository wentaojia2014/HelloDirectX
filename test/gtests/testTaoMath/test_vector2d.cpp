#include <TaoMath/TaoMath>
#include <gtest/gtest.h>
using namespace TaoMath;
TEST(testVector2D, test1)
{
    Vector2D p1;
    ASSERT_TRUE(p1.isNull());
    Vector2D p2(1, 2);
    ASSERT_TRUE(fuzzyCompare(p2.x(), 1));
    ASSERT_TRUE(fuzzyCompare(p2.y(), 2));

    Vector2D p3(p2);
    ASSERT_TRUE(fuzzyCompare(p3.x(), 1));
    ASSERT_TRUE(fuzzyCompare(p3.y(), 2));
    ASSERT_TRUE(fuzzyCompare(p3.length(), 2.23606f));
    p3.setX(p3.x() + 1);
    ASSERT_EQ(p3.x(), 2);
    p3.setY(p3.y() + 1);
    ASSERT_EQ(p3.y(), 3);
}
TEST(testVector2D, test2)
{
    Vector2D p1(10, 4);
    p1 += 3;
    ASSERT_TRUE(Vector2D(13, 7) == p1);
    p1 += 1.5;
    ASSERT_TRUE(Vector2D(14.5f, 8.5f) == p1);
    p1 += Vector2D(1, 2);
    ASSERT_TRUE(Vector2D(15.5f, 10.5f) == p1);

    p1 -= 3;
    ASSERT_TRUE(Vector2D(12.5f, 7.5f) == p1);
    p1 -= 2.1;
    ASSERT_TRUE(Vector2D(10.4f, 5.4f) == p1);

    p1 -= Vector2D(1, 2);

    ASSERT_TRUE(Vector2D(9.4f, 3.4f) == p1);

    p1 *= 2;
    ASSERT_EQ(Vector2D(18.8f, 6.8f), p1);
    p1 *= 0.1;
    ASSERT_EQ(Vector2D(1.88f, 0.68f), p1);

    p1 /= 0.5;
    ASSERT_EQ(Vector2D(3.76f, 1.36f), p1);

    p1 /= 2;
    ASSERT_EQ(Vector2D(1.88f, 0.68f), p1);

    p1 *= Vector2D(2.0f, 2.0f);
    ASSERT_EQ(Vector2D(3.76f, 1.36f), p1);

    p1 /= Vector2D(2.0f, 2.0f);
    ASSERT_EQ(Vector2D(1.88f, 0.68f), p1);

    p1 /= 0.0;
}
TEST(testVector2D, test3)
{
    Vector2D p1(2, 2);
    Vector2D p2(3, 3);
    auto     p = Vector2D::dotProduct(p1, p2);
    ASSERT_EQ(p, 12);
}
TEST(testVector2D, test4)
{
    Vector2D p1(2, 2);
    Vector2D p2(3, 3);
    Vector2D p3(3, 3);
    ASSERT_TRUE(p2 == p3);
    ASSERT_TRUE(p1 != p2);
    {
        auto p = p1 + p2;
        ASSERT_EQ(p1, Vector2D(2, 2));
        ASSERT_EQ(p, Vector2D(5, 5));
    }
    {
        auto p = p1 - p2;
        ASSERT_EQ(p, Vector2D(-1, -1));
    }
    {
        auto p = p1 * 3;
        ASSERT_EQ(p, Vector2D(6, 6));
    }
    {
        auto p = p1 * 2.5;
        ASSERT_EQ(p, Vector2D(5, 5));
    }
    {
        auto p = 3 * p1;
        ASSERT_EQ(p, Vector2D(6, 6));
    }
    {
        auto p = 2.5 * p1;
        ASSERT_EQ(p, Vector2D(5, 5));
    }
    {
        auto p = p1 / 2;
        ASSERT_EQ(p, Vector2D(1, 1));
    }
    {
        auto p = p1 / 0.5;
        ASSERT_EQ(p, Vector2D(4, 4));
    }
    {
        Vector2D v(1., 2);
        auto     v1 = v * 3;
        auto     v2 = 3 * v;
        ASSERT_EQ(v1, Vector2D(3, 6));
        ASSERT_EQ(v2, Vector2D(3, 6));
    }
    {
        Vector2D v(12, 9);
        auto     v1 = v / 3;
        ASSERT_EQ(v1, Vector2D(4., 3.));
        auto v0 = v / 1.0;
        ASSERT_EQ(v0, Vector2D(12, 9));
    }
}
TEST(testVector2D, test5)
{
    Vector2D v(1.3f, 2.4f);
    auto     p = v.toPoint();
    ASSERT_EQ(Point(1, 2), p);

    auto p2 = v.toPointF();
    ASSERT_EQ(PointF(1.3f, 2.4f), p2);

    auto v3 = v.toVector3D();
    ASSERT_EQ(Vector3D(1.3f, 2.4f, 0), v3);

    auto v4 = v.toVector4D();
    ASSERT_EQ(Vector4D(1.3f, 2.4f, 0.0f, 0.f), v4);
}
TEST(testVector2D, test6)
{
    {
        Point    p1(1, 2);
        Vector2D v(p1);
        ASSERT_EQ(v, Vector2D(1, 2));
    }
    {
        PointF   p1(1.1f, 2.2f);
        Vector2D v(p1);
        ASSERT_EQ(v, Vector2D(1.1f, 2.2f));
    }
    {
        Vector3D v3(1.1f, 2.2f, 3.3f);
        Vector2D v(v3);
        ASSERT_EQ(v, Vector2D(1.1f, 2.2f));
    }
    {
        Vector4D v4(1.1f, 2.2f, 3.3f, 4.4f);
        Vector2D v(v4);
        ASSERT_EQ(v, Vector2D(1.1f, 2.2f));
    }
}
TEST(testVector2D, test7)
{
    Vector2D v(3., 4.);
    ASSERT_EQ(1.0, v.distanceToPoint({ 4., 4. }));
    ASSERT_EQ(1.0, v.distanceToLine({ 4., 4. }, { 0.0, 10.0 }));
    ASSERT_EQ(5., v.distanceToPoint(Vector2D()));
    Vector2D v0;
    ASSERT_EQ(5.0, v0.distanceToPoint({ 3., 4. }));
    ASSERT_EQ(4.0, v0.distanceToLine({ 3., 4. }, { 10.0, 0.0 }));

    Vector2D v3(1, 1);
    ASSERT_EQ(v3.distanceToLine({ 2., 2. }, { -1., 1. }), 1.4142135623730951f);
    Vector2D v4(1, 1);
    ASSERT_EQ(v4.distanceToLine({ 2., 2. }, {}), 1.4142135623730951f);
}
TEST(testVector2D, test8)
{
    Vector2D v(3.3f, 4.4f);
    auto     vn = v.normalized();
    v.normalize();
    ASSERT_EQ(v, vn);
    ASSERT_EQ(Vector2D(0.6f, 0.8f), v);
    {
        Vector2D v2(0.6f, 0.8f);
        auto     vn2 = v2.normalized();
        ASSERT_EQ(v2, vn2);
    }
    {
        Vector2D v;
        v = v.normalized();
        ASSERT_TRUE(v.isNull());
    }
    {
        Vector2D v;
        v.normalize();
        ASSERT_TRUE(v.isNull());
    }
    {
        Vector2D v(1.2f, 1.6f);
        v.normalize();
        ASSERT_EQ(v, Vector2D(0.6f, 0.8f));
    }
}
TEST(testVector2D, test9)
{
    Vector2D v(3., 4.);
    ASSERT_EQ(25, v.lengthSquared());
    ASSERT_EQ(5, v.length());
}
