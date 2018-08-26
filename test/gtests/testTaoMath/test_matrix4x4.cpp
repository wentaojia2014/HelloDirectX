#include <TaoMath/TaoMath>
#include <gtest/gtest.h>

using namespace TaoMath;
TEST(test_matrix4x4, test1)
{
    Matrix4x4 m44(1, 2, 3, 4,
        4, 3, 2, 1,
        1, 2, 2, 1,
        1, 3, 2, 4);
    ASSERT_EQ(Vector4D(1, 2, 3, 4), m44.row(0));
    ASSERT_EQ(Vector4D(4, 3, 2, 1), m44.row(1));
    ASSERT_EQ(Vector4D(1, 2, 2, 1), m44.row(2));
    ASSERT_EQ(Vector4D(1, 3, 2, 4), m44.row(3));

    ASSERT_EQ(Vector4D(1, 4, 1, 1), m44.column(0));
    ASSERT_EQ(Vector4D(2, 3, 2, 3), m44.column(1));
    ASSERT_EQ(Vector4D(3, 2, 2, 2), m44.column(2));
    ASSERT_EQ(Vector4D(4, 1, 1, 4), m44.column(3));
    m44.setRow(0, Vector4D(1, 2, 4, 3));
    ASSERT_EQ(Vector4D(1, 2, 4, 3), m44.row(0));

    m44.setColumn(1, Vector4D(1, 2, 3, 4));
    ASSERT_EQ(Vector4D(1, 2, 3, 4), m44.column(1));
}
TEST(test_matrix4x4, test2)
{
    Matrix4x4 m44(1, 2, 3, 4,
        4, 3, 2, 1,
        1, 2, 2, 1,
        1, 3, 2, 4);
    Matrix4x4 m2(1, 2, 3, 4,
        4, 3, 2, 1,
        1, 2, 2, 1,
        1, 3, 2, 4);
    m44 *= m2;
    ASSERT_EQ(Vector4D(16, 26, 21, 25), m44.row(0));
    ASSERT_EQ(Vector4D(19, 24, 24, 25), m44.row(1));
    ASSERT_EQ(Vector4D(12, 15, 13, 12), m44.row(2));
    ASSERT_EQ(Vector4D(19, 27, 21, 25), m44.row(3));

    auto m3 = m2 * m2;
    ASSERT_EQ(Vector4D(16, 26, 21, 25), m3.row(0));
    ASSERT_EQ(Vector4D(19, 24, 24, 25), m3.row(1));
    ASSERT_EQ(Vector4D(12, 15, 13, 12), m3.row(2));
    ASSERT_EQ(Vector4D(19, 27, 21, 25), m3.row(3));
}
TEST(test_matrix4x4, test3)
{
    Matrix4x4 m44(1, 2, 3, 4,
        4, 3, 2, 1,
        1, 2, 2, 1,
        1, 3, 2, 4);
    Vector4D v(1, 2, 3, 4);
    auto res = v * m44;

    ASSERT_EQ(res, Vector4D(16, 26, 21, 25));
    real* p = m44.data ();
    (void)p;
    const real *pp = m44.data ();
    (void)pp;
    const real *ppp = m44.constData ();
    (void)ppp;
}

TEST (test_matrix4x4, test4) {
    Matrix4x4 m44 (1, 2, 3, 4,
                   4, 3, 2, 1,
                   1, 2, 2, 1,
                   1, 3, 2, 4);
    auto m2 = m44;
    m44 += 1.0f;
    m44 -= 1.0f;
    ASSERT_EQ (m2, m44);
}
TEST (test_matrix4x4, test5) {
    Matrix4x4 m44 (1, 2, 3, 4,
                   4, 3, 2, 1,
                   1, 2, 2, 1,
                   1, 3, 2, 4);
    auto m2 = m44 + 1;
    auto m3 = m44 - 1;
    ASSERT_TRUE (m2 != m3);
    ASSERT_FALSE (fuzzyCompare (m2, m3));
    m3 += 2;
    ASSERT_EQ (m2, m3);
    ASSERT_TRUE (fuzzyCompare (m2, m3));
    
}