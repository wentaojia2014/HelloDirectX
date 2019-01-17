#include <TaoMath/TaoMath>
#include <gtest/gtest.h>
using namespace TaoMath;
TEST(testVector3D, test1)
{
    Vector3D p1;
    ASSERT_TRUE(p1.isNull());
    Vector3D p2(1, 2, 3);
    ASSERT_TRUE(fuzzyCompare(p2.x(), 1));
    ASSERT_TRUE(fuzzyCompare(p2.y(), 2));
    ASSERT_TRUE(fuzzyCompare(p2.z(), 3));
    Vector3D p3(p2);
    ASSERT_TRUE(fuzzyCompare(p3.x(), 1));
    ASSERT_TRUE(fuzzyCompare(p3.y(), 2));
    ASSERT_TRUE(fuzzyCompare(p3.z(), 3));
    ASSERT_TRUE(fuzzyCompare(p3.length(), 3.741657386773941f));
    p3.setX(p3.x() + 1);
    ASSERT_EQ(p3.x(), 2);
    p3.setY(p3.y() + 1);
    ASSERT_EQ(p3.y(), 3);
    p3.setZ(p3.z() + 1);
    ASSERT_EQ(p3.z(), 4);
}
TEST(testVector3D, test2)
{
    Vector3D p1(10, 4, 1);
    p1 += 3;
    ASSERT_TRUE(Vector3D(13, 7, 4) == p1);
    p1 += 1.5;
    ASSERT_TRUE(Vector3D(14.5, 8.5, 5.5) == p1);
    p1 += Vector3D(1, 2, 3);
    ASSERT_TRUE(Vector3D(15.5, 10.5, 8.5) == p1);

    p1 -= 3;
    ASSERT_TRUE(Vector3D(12.5, 7.5, 5.5) == p1);
    p1 -= 2.1;
    ASSERT_TRUE(Vector3D(10.4, 5.4, 3.4) == p1);

    p1 -= Vector3D(1, 2, 2);
    ASSERT_TRUE(Vector3D(9.4, 3.4, 1.4) == p1);

    p1 *= 2;
    ASSERT_EQ(Vector3D(18.8, 6.8, 2.8), p1);
    p1 *= 0.1;
    ASSERT_EQ(Vector3D(1.88, 0.68, 0.28), p1);

    p1 /= 0.5;
    ASSERT_EQ(p1, Vector3D(3.76, 1.36, 0.56));

    p1 /= 2;
    ASSERT_EQ(Vector3D(1.88, 0.68, 0.28), p1);

    p1 *= Vector3D(2.0, 2.0, 2.0);
    ASSERT_EQ(Vector3D(3.76, 1.36, 0.56), p1);

    p1 /= Vector3D(2.0, 2.0, 2.0);
    ASSERT_EQ(Vector3D(1.88, 0.68, 0.28), p1);

    p1 /= 0.0;
}
TEST(testVector3D, test3)
{
    Vector3D p1(2, 2, 2);
    Vector3D p2(3, 3, 3);
    auto     p = Vector3D::dotProduct(p1, p2);
    ASSERT_EQ(p, 18);
    auto pp = Vector3D::crossProduct(p1, p2);
    ASSERT_TRUE(pp.isNull());
}
TEST(testVector3D, test4)
{
    Vector3D p1(2, 2, 2);
    Vector3D p2(3, 3, 3);
    Vector3D p3(3, 3, 3);
    ASSERT_TRUE(p2 == p3);
    ASSERT_TRUE(p1 != p2);
    {
        auto p = p1 + p2;
        ASSERT_EQ(p1, Vector3D(2, 2, 2));
        ASSERT_EQ(p, Vector3D(5, 5, 5));
    }
    {
        auto p = p1 - p2;
        ASSERT_EQ(p, Vector3D(-1, -1, -1));
    }
    {
        auto p = p1 * 3;
        ASSERT_EQ(p, Vector3D(6, 6, 6));
    }
    {
        auto p = p1 * 2.5;
        ASSERT_EQ(p, Vector3D(5, 5, 5));
    }
    {
        auto p = 3 * p1;
        ASSERT_EQ(p, Vector3D(6, 6, 6));
    }
    {
        auto p = 2.5 * p1;
        ASSERT_EQ(p, Vector3D(5, 5, 5));
    }
    {
        auto p = p1 / 2;
        ASSERT_EQ(p, Vector3D(1, 1, 1));
    }
    {
        auto p = p1 / 0.5;
        ASSERT_EQ(p, Vector3D(4, 4, 4));
    }
    {
        Vector3D v(1, 2, 3);
        auto     v1 = v * 3;
        auto     v2 = 3 * v;
        ASSERT_EQ(v1, Vector3D(3, 6, 9));
        ASSERT_EQ(v2, Vector3D(3, 6, 9));
    }
    {
        Vector3D v(12, 9, 6);
        auto     v1 = v / 3;
        ASSERT_EQ(v1, Vector3D(4, 3, 2));
        auto v0 = v / 1.0;
        ASSERT_EQ(v0, Vector3D(12, 9, 6));
    }
}
TEST(testVector3D, test5)
{
    Vector3D v(1.3, 2.4, 2.3);
    auto     p = v.toPoint();
    ASSERT_EQ(Point(1, 2), p);

    auto p2 = v.toPointF();
    ASSERT_EQ(PointF(1.3, 2.4), p2);

    auto v3 = v.toVector2D();
    ASSERT_EQ(Vector2D(1.3, 2.4), v3);

    auto v4 = v.toVector4D();
    ASSERT_EQ(Vector4D(1.3, 2.4, 2.3, 0), v4);
}
TEST(testVector3D, test6)
{
    {
        Point    p1(1, 2);
        Vector3D v(p1);
        ASSERT_EQ(v, Vector3D(1, 2, 0));
    }
    {
        PointF   p1(1.1, 2.2);
        Vector3D v(p1);
        ASSERT_EQ(v, Vector3D(1.1, 2.2, 0.0));
    }
    {
        Vector2D v2(1.1, 2.2);
        Vector3D v(v2);
        ASSERT_EQ(v, Vector3D(1.1, 2.2, 0.0));
    }
    {
        Vector4D v4(1.1, 2.2, 3.3, 4.4);
        Vector3D v(v4);
        ASSERT_EQ(v, Vector3D(1.1, 2.2, 3.3));
    }
}
TEST(testVector3D, test7)
{
    Vector3D v(3., 4., 5);
    ASSERT_TRUE(
        fuzzyCompare(1.4142135623730951f, v.distanceToPoint({ 4., 4., 4 })));
    ASSERT_TRUE(fuzzyCompare(
        1.4142135623730951f,
        v.distanceToLine({ 4., 4., 4. }, { 0.0, 1.0, 0.0 })));
    ASSERT_TRUE(
        fuzzyCompare(7.071067811865475f, v.distanceToPoint(Vector3D())));
    Vector3D v0;
    ASSERT_TRUE(fuzzyCompare(
        297.069015550259f,
        v0.distanceToLine({ 3., 4., 5. }, { 10.0, 0.0, 0. })));

    Vector3D v3(1, 1, 1);
    ASSERT_TRUE(
        fuzzyCompare(v3.distanceToLine({ 2, 2, 2 }, { -1, 1, 1 }), 2.f));
    Vector3D v4(1, 1, 1);
    ASSERT_TRUE(
        fuzzyCompare(v4.distanceToLine({ 2, 2, 2 }, {}), 1.732050807568877f));

    Vector3D v5;
    ASSERT_TRUE(fuzzyCompare(v5.distanceToPlane({ 1, 1, 1 }, { 0, 1, 0 }), -1));
    Vector3D v6(1, 1, 1);
    ASSERT_TRUE(fuzzyCompare(
        v6.distanceToPlane(
            { 2, 2, 2 },
            {
                3,
                3,
                3,
            },
            { 4, 4, 4 }),
        0));
}
TEST(testVector3D, test8)
{
    Vector3D v(3.3, 4.4, 5.5);
    auto     vn = v.normalized();
    v.normalize();
    ASSERT_EQ(v, vn);
    ASSERT_EQ(
        Vector3D(
            0.42426406871192851464050661726291,
            0.56568542494923801952067548968388,
            0.70710678118654752440084436210485),
        v);
    {
        Vector3D v2(
            0.42426406871192851464050661726291,
            0.56568542494923801952067548968388,
            0.70710678118654752440084436210485);
        auto vn2 = v2.normalized();
        ASSERT_EQ(v2, vn2);
    }
    {
        Vector3D v;
        v = v.normalized();
        ASSERT_TRUE(v.isNull());
    }
    {
        Vector3D v;
        v.normalize();
        ASSERT_TRUE(v.isNull());
    }
    {
        Vector3D v(1.2, 1.6, 1.8);
        v.normalize();
        ASSERT_EQ(
            v,
            Vector3D(
                0.44597648774829978951921830261338,
                0.59463531699773305269229107015117,
                0.66896473162244968427882745392007));
    }
}
TEST(testVector3D, test9)
{
    Vector3D v(3., 4., 5.);
    ASSERT_EQ(50, v.lengthSquared());
    ASSERT_TRUE(fuzzyCompare(7.071067811865475f, v.length()));
}
TEST(testVector3D, test10)
{
    auto v = Vector3D::normal(
        Vector3D(1, 1, 1), Vector3D(2, 2, 2), Vector3D(3, 3, 3));
    ASSERT_EQ(v, Vector3D());
}