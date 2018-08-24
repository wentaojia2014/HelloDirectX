#include <TaoMath/TaoMath>
#include <gtest/gtest.h>
#include <iostream>
using std::cout;
using std::endl;

using namespace TaoMath;

template <typename MatrixType>
struct Tester {
    static void test1 () {
        MatrixType m1;
        ASSERT_TRUE (m1.isIdentity ());
        MatrixType m2 (State::Uninitialized);
        ASSERT_FALSE (m2.isIdentity ());
        m2.fill (1.0);
        ASSERT_FALSE (m2.isIdentity ());
        ASSERT_NE (m1, m2);
        ASSERT_TRUE (m1 != m2);

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
        MatrixType m3 (values);
        for (int i = 0; i < m3.rowCount (); ++i) {
            for (int j = 0; j < m3.columnCount (); ++j) {
                ASSERT_EQ (m3 (i, j), values[i * m3.columnCount () + j]);
            }
        }
        auto m4 = m3.transposed ();
        for (int i = 0; i < m3.rowCount (); ++i) {
            for (int j = 0; j < m3.columnCount (); ++j) {
                ASSERT_EQ (m3 (i, j), m4 (j, i));
            }
        }
        auto m5 = m3;
        ASSERT_EQ (m5, m3);
        m5 *= 2.0;
        m5 /= 2.0;
        m5 += m3;
        m5 -= m3;
        ASSERT_EQ (m5, m3);

        m5 *= 0.1f;
        ASSERT_NE (m5, m3);

        auto m6 = m3 + m3;
        m6 = m6 - m3;
        ASSERT_EQ (m6, m3);
        auto m7 = -m3;
        m7 = -m7;
        ASSERT_EQ (m7, m3);
        MatrixType m8 = m3 * 2.f;
        MatrixType m9 = 2.f * m3;
        ASSERT_EQ (m8, m9);
        m8 = m8 / 2.f;
        ASSERT_EQ (m8, m3);
        m9 = m9 / 2.0f;
        ASSERT_EQ (m9, m3);
    }
};

template <typename First, typename... Args>
struct MatrixIterator {
    static void iterator()
    {
        Tester<First>::test1 ();
        //back-tracer
        MatrixIterator<Args...>::iterator ();
    }
};
template <typename Last>
struct MatrixIterator<Last> {
    static void iterator ()
    {
        Tester<Last>::test1 ();
    }
};

TEST(test_matrixGeneric, test1)
{
    MatrixIterator<Matrix2x2, Matrix2x3, Matrix2x4,
        Matrix3x2, Matrix3x3, Matrix3x4,
        Matrix4x2, Matrix4x3, Matrix4x4>::iterator ();
}
