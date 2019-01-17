#include <TaoMath/TaoMath>
#include <gtest/gtest.h>
using namespace TaoMath;
TEST(testVector4D, test1)
{
    Vector4D p1;
    ASSERT_TRUE(p1.isNull());
    Vector4D p2(1, 2, 3, 4);
    ASSERT_TRUE(fuzzyCompare(p2.x(), 1));
    ASSERT_TRUE(fuzzyCompare(p2.y(), 2));
    ASSERT_TRUE(fuzzyCompare(p2.z(), 3));
    ASSERT_TRUE(fuzzyCompare(p2.w(), 4));
    Vector4D p3(p2);
    ASSERT_TRUE(fuzzyCompare(p3.x(), 1));
    ASSERT_TRUE(fuzzyCompare(p3.y(), 2));
    ASSERT_TRUE(fuzzyCompare(p3.z(), 3));
    ASSERT_TRUE(fuzzyCompare(p3.w(), 4));
    ASSERT_TRUE(fuzzyCompare(p3.length(), 5.477225575051661134569697828008f));
    p3.setX(p3.x() + 1);
    ASSERT_EQ(p3.x(), 2);
    p3.setY(p3.y() + 1);
    ASSERT_EQ(p3.y(), 3);
    p3.setZ(p3.z() + 1);
    ASSERT_EQ(p3.z(), 4);
    p3.setW(p3.w() + 1);
    ASSERT_EQ(p3.w(), 5);
}
TEST(testVector4D, test2)
{
    Vector4D p1(10, 4, 1, 1);
    p1 += 3;
    ASSERT_TRUE(Vector4D(13, 7, 4, 4) == p1);
    p1 += 1.5;
    ASSERT_TRUE(Vector4D(14.5, 8.5, 5.5, 5.5) == p1);
    p1 += Vector4D(1, 2, 3, 3);
    ASSERT_TRUE(Vector4D(15.5, 10.5, 8.5, 8.5) == p1);

    p1 -= 3;
    ASSERT_TRUE(Vector4D(12.5, 7.5, 5.5, 5.5) == p1);
    p1 -= 2.1;
    ASSERT_TRUE(Vector4D(10.4, 5.4, 3.4, 3.4) == p1);

    p1 -= Vector4D(1, 2, 2, 2);
    ASSERT_TRUE(Vector4D(9.4, 3.4, 1.4, 1.4) == p1);

    p1 *= 2;
    ASSERT_EQ(Vector4D(18.8, 6.8, 2.8, 2.8), p1);
    p1 *= 0.1;
    ASSERT_EQ(Vector4D(1.88, 0.68, 0.28, 0.28), p1);

    p1 /= 0.5;
    ASSERT_EQ(p1, Vector4D(3.76, 1.36, 0.56, 0.56));

    p1 /= 2;
    ASSERT_EQ(Vector4D(1.88, 0.68, 0.28, 0.28), p1);

    p1 *= Vector4D(2.0, 2.0, 2.0, 2.0);
    ASSERT_EQ(Vector4D(3.76, 1.36, 0.56, 0.56), p1);

    p1 /= Vector4D(2.0, 2.0, 2.0, 2.0);
    ASSERT_EQ(Vector4D(1.88, 0.68, 0.28, 0.28), p1);

    p1 /= 0.0;
}
TEST(testVector4D, test3)
{
    Vector4D p1(2, 2, 2, 2);
    Vector4D p2(3, 3, 3, 3);
    auto     p = Vector4D::dotProduct(p1, p2);
    ASSERT_EQ(p, 24);
}
TEST(testVector4D, test4)
{
    Vector4D p1(2, 2, 2, 2);
    Vector4D p2(3, 3, 3, 3);
    Vector4D p3(3, 3, 3, 3);
    ASSERT_TRUE(p2 == p3);
    ASSERT_TRUE(p1 != p2);
    {
        auto p = p1 + p2;
        ASSERT_EQ(p1, Vector4D(2, 2, 2, 2));
        ASSERT_EQ(p, Vector4D(5, 5, 5, 5));
    }
    {
        auto p = p1 - p2;
        ASSERT_EQ(p, Vector4D(-1, -1, -1, -1));
    }
    {
        auto p = p1 * 3;
        ASSERT_EQ(p, Vector4D(6, 6, 6, 6));
    }
    {
        auto p = p1 * 2.5;
        ASSERT_EQ(p, Vector4D(5, 5, 5, 5));
    }
    {
        auto p = 3 * p1;
        ASSERT_EQ(p, Vector4D(6, 6, 6, 6));
    }
    {
        auto p = 2.5 * p1;
        ASSERT_EQ(p, Vector4D(5, 5, 5, 5));
    }
    {
        auto p = p1 / 2;
        ASSERT_EQ(p, Vector4D(1, 1, 1, 1));
    }
    {
        auto p = p1 / 0.5;
        ASSERT_EQ(p, Vector4D(4, 4, 4, 4));
    }
    {
        Vector4D v(1, 2, 3, 3);
        auto     v1 = v * 3;
        auto     v2 = 3 * v;
        ASSERT_EQ(v1, Vector4D(3, 6, 9, 9));
        ASSERT_EQ(v2, Vector4D(3, 6, 9, 9));
    }
    {
        Vector4D v(12, 9, 6, 6);
        auto     v1 = v / 3;
        ASSERT_EQ(v1, Vector4D(4, 3, 2, 2));
        auto v0 = v / 1.0;
        ASSERT_EQ(v0, Vector4D(12, 9, 6, 6));
    }
}
TEST(testVector4D, test5)
{
    Vector4D v(1.3, 2.4, 2.3, 2.3);
    auto     p = v.toPoint();
    ASSERT_EQ(Point(1, 2), p);

    auto p2 = v.toPointF();
    ASSERT_EQ(PointF(1.3, 2.4), p2);

    auto v3 = v.toVector2D();
    ASSERT_EQ(Vector2D(1.3, 2.4), v3);

    auto v4 = v.toVector3D();
    ASSERT_EQ(Vector3D(1.3, 2.4, 2.3), v4);
}
TEST(testVector4D, test6)
{
    {
        Point    p1(1, 2);
        Vector4D v(p1);
        ASSERT_EQ(v, Vector4D(1, 2, 0, 0));
    }
    {
        PointF   p1(1.1, 2.2);
        Vector4D v(p1);
        ASSERT_EQ(v, Vector4D(1.1, 2.2, 0.0, 0.0));
    }
    {
        Vector2D v2(1.1, 2.2);
        Vector4D v(v2);
        ASSERT_EQ(v, Vector4D(1.1, 2.2, 0.0, 0.0));
    }
    {
        Vector3D v4(1.1, 2.2, 3.3);
        Vector4D v(v4);
        ASSERT_EQ(v, Vector4D(1.1, 2.2, 3.3, 0));
    }
}
TEST(testVector4D, test8)
{
    Vector4D v(3.3, 4.4, 5.5, 5.5);
    auto     vn = v.normalized();
    v.normalize();
    ASSERT_EQ(v, vn);
    // 9.5262794416288251144009548782823
    ASSERT_EQ(
        Vector4D(
            0.34641016151377545870548926830117,
            0.46188021535170061160731902440157,
            0.57735026918962576450914878050196,
            0.57735026918962576450914878050196),
        v);
    {
        Vector4D v2(
            0.34641016151377545870548926830117,
            0.46188021535170061160731902440157,
            0.57735026918962576450914878050196,
            0.57735026918962576450914878050196);
        auto vn2 = v2.normalized();
        ASSERT_EQ(v2, vn2);
    }
    {
        Vector4D v;
        v = v.normalized();
        ASSERT_TRUE(v.isNull());
    }
    {
        Vector4D v;
        v.normalize();
        ASSERT_TRUE(v.isNull());
    }
    {
        Vector4D v(1.2, 1.6, 1.8, 2.0);
        v.normalize();
        // 3.3526109228480420256891391113032
        ASSERT_EQ(
            v,
            Vector4D(
                0.35792999176313615932624260974768,
                0.4772399890175148791016568129969,
                0.53689498764470423898936391462151,
                0.59654998627189359887707101624613));
    }
}
TEST(testVector4D, test9)
{
    Vector4D v(3., 4., 5., 6.);
    ASSERT_EQ(86, v.lengthSquared());
    ASSERT_TRUE(fuzzyCompare(9.2736184954957037525164160739902f, v.length()));
}
