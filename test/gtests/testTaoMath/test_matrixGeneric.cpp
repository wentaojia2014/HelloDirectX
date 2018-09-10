#include <TaoMath/TaoMath>
#include <gtest/gtest.h>

using namespace TaoMath;

template <typename MatrixType> struct Tester
{
    static void test1()
    {
        MatrixType m1;
        ASSERT_TRUE(m1.isIdentity());
        MatrixType m2(State::Uninitialized);
        ASSERT_FALSE(m2.isIdentity());
        m2.fill(1.0);
        ASSERT_FALSE(m2.isIdentity());
        ASSERT_NE(m1, m2);
        ASSERT_TRUE(m1 != m2);
        ASSERT_FALSE(m1 == m2);
        const static real values[] = {
            0.1, 0.2, 0.3, 0.4, 0.1, 0.2, 0.3, 0.4,
            0.1, 0.2, 0.3, 0.4, 0.1, 0.2, 0.3, 0.4,
        };
        MatrixType m3(values);
        for (int i = 0; i < m3.rowCount(); ++i)
        {
            for (int j = 0; j < m3.columnCount(); ++j)
            {
                ASSERT_EQ(m3(i, j), values[i * m3.columnCount() + j]);
            }
        }
        real values2[16];
        m3.copyDataTo(values2);
        MatrixType m0(static_cast<const real *>(&values2[0]));
        ASSERT_EQ(m0, m3);

        auto m4 = m3.transposed();
        for (int i = 0; i < m3.rowCount(); ++i)
        {
            for (int j = 0; j < m3.columnCount(); ++j)
            {
                ASSERT_EQ(m3(i, j), m4(j, i));
            }
        }
        auto m5 = m3;
        ASSERT_EQ(m5, m3);
        m5 *= 2.0;
        m5 /= 2.0;
        m5 += m3;
        m5 -= m3;
        ASSERT_EQ(m5, m3);
        ASSERT_TRUE(m5 == m3);
        ASSERT_FALSE(m5 != m3);

        m5 *= 0.1f;
        ASSERT_NE(m5, m3);

        auto m6 = m3 + m3;
        m6      = m6 - m3;
        ASSERT_EQ(m6, m3);
        auto m7 = -m3;
        m7      = -m7;
        ASSERT_EQ(m7, m3);
        MatrixType m8 = m3 * 2.f;
        MatrixType m9 = 2.f * m3;
        ASSERT_EQ(m8, m9);
        m8 = m8 / 2.f;
        ASSERT_EQ(m8, m3);
        m9 = m9 / 2.0f;
        ASSERT_EQ(m9, m3);
    }
};

template <typename First, typename... Args> struct MatrixIterator
{
    static void iterator()
    {
        Tester<First>::test1();
        // back-tracer
        MatrixIterator<Args...>::iterator();
    }
};
template <typename Last> struct MatrixIterator<Last>
{
    static void iterator()
    {
        Tester<Last>::test1();
    }
};

TEST(test_matrixGeneric, test1)
{
    MatrixIterator<
        Matrix2x2,
        Matrix2x3,
        Matrix2x4,
        Matrix3x2,
        Matrix3x3,
        Matrix3x4,
        Matrix4x2,
        Matrix4x3,
        Matrix4x4>::iterator();
}
TEST(test_matrixGeneric, test2)
{
    Matrix2x3 m23;
    m23(0, 0) = 1;
    m23(0, 1) = 2;
    m23(0, 2) = 3;

    m23(1, 0) = 2;
    m23(1, 1) = 2;
    m23(1, 2) = 1;

    Matrix3x2 m32;

    m32(0, 0) = 2;
    m32(0, 1) = 3;
    m32(1, 0) = 1;
    m32(1, 1) = 2;
    m32(2, 0) = 2;
    m32(2, 1) = 2;

    auto ans = m23 * m32;
    ASSERT_EQ(ans(0, 0), 10);
    ASSERT_EQ(ans(0, 1), 13);
    ASSERT_EQ(ans(1, 0), 8);
    ASSERT_EQ(ans(1, 1), 12);
}
