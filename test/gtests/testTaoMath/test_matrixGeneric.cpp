#include <TaoMath/TaoMath>
#include <gtest/gtest.h>
#include <iostream>
using std::cout;
using std::endl;

using namespace TaoMath;

template <typename First, typename... Args>
struct MatrixTester {
    static void test1()
    {
        First m1;
        ASSERT_TRUE(m1.isIdentity());
        First m2(State::Uninitialized);
        ASSERT_FALSE(m2.isIdentity());

        const static real values[] = {
            0.1,
            0.2,
            0.3,
            0.4,
            0.1,
            0.2,
            0.3,
            0.4,
            0.1,
            0.2,
            0.3,
            0.4,
            0.1,
            0.2,
            0.3,
            0.4,
        };
        First m3(values);
        for (int i = 0; i < m3.rowCount(); ++i) {
            for (int j = 0; j < m3.columnCount(); ++j) {
                ASSERT_EQ(m3(i, j), values[i * m3.columnCount() + j]);
            }
        }
        auto m4 = m3.transposed();
        for (int i = 0; i < m3.rowCount(); ++i) {
            for (int j = 0; j < m3.columnCount(); ++j) {
                ASSERT_EQ(m3(i, j), m4(j, i));
            }
        }
        auto m5 = m3;
        ASSERT_EQ (m5, m3);
        m5 *= 2.0;
        m5 /= 2.0;
        m5 += m3;
        m5 -= m3;
        ASSERT_EQ (m5, m3);
      
        m5 *= 0.1;
        ASSERT_NE (m5, m3);
        //back-tracer
        MatrixTester<Args...>::test1();
    }
};
template <typename Last>
struct MatrixTester<Last> {
    static void test1()
    {
        Last m1;
        ASSERT_TRUE(m1.isIdentity());

        Last m2(State::Uninitialized);
        ASSERT_FALSE(m2.isIdentity());

        const static real values[] = {
            0.1,
            0.2,
            0.3,
            0.4,
            0.1,
            0.2,
            0.3,
            0.4,
            0.1,
            0.2,
            0.3,
            0.4,
            0.1,
            0.2,
            0.3,
            0.4,
        };
        Last m3(values);
        for (int i = 0; i < m3.rowCount(); ++i) {
            for (int j = 0; j < m3.columnCount(); ++j) {
                ASSERT_EQ(m3(i, j), values[i * m3.columnCount() + j]);
            }
        }
        auto m4 = m3.transposed();
        for (int i = 0; i < m3.rowCount(); ++i) {
            for (int j = 0; j < m3.columnCount(); ++j) {
                ASSERT_EQ(m3(i, j), m4(j, i));
            }
        }
        auto m5 = m3;
        ASSERT_EQ (m5, m3);
        m5 *= 2.0;
        m5 /= 2.0;
        m5 += m3;
        m5 -= m3;
        ASSERT_EQ (m5, m3);
      
        m5 *= 0.1;
        ASSERT_NE (m5, m3);
    }
};

TEST(test_matrixGeneric, test1)
{
    MatrixTester<Matrix2x2, Matrix2x3, Matrix2x4,
        Matrix3x2, Matrix3x3, Matrix3x4,
        Matrix4x2, Matrix4x3, Matrix4x4>::test1();
}
