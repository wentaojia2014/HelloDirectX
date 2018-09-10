#pragma once
#include "Common.hpp"
#include "Global.h"
#include "TaoMathFwd"
#include "Vector4D.hpp"
namespace TaoMath
{

class TAOEXPORT Matrix4x4
{
    static constexpr int W = 4;
    static constexpr int H = 4;

public:
    inline Matrix4x4()
    {
        setToIdentity();
    }
    constexpr inline Matrix4x4(State) {}
    inline Matrix4x4(
        real m00,
        real m01,
        real m02,
        real m03,
        real m10,
        real m11,
        real m12,
        real m13,
        real m20,
        real m21,
        real m22,
        real m23,
        real m30,
        real m31,
        real m32,
        real m33)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
        m[3][0] = m30;
        m[3][1] = m31;
        m[3][2] = m32;
        m[3][3] = m33;
    }
    inline Matrix4x4(const real *values)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] = values[i * H + j];
            }
        }
    }
    inline Matrix4x4(const Matrix4x4 &o)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] = o.m[i][j];
            }
        }
    }
    inline void fill(real v)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] = v;
            }
        }
    }
    const Vector4D row(int r) const;
    void           setRow(int r, const Vector4D &v);
    const Vector4D column(int c) const;
    void           setColumn(int c, const Vector4D &v);

    constexpr inline int rowCount() const
    {
        return W;
    }
    constexpr inline int columnCount() const
    {
        return H;
    }

    inline void transpose()
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = i + 1; j < H; ++j)
            {
                std::swap(m[i][j], m[j][i]);
            }
        }
    }
    inline Matrix4x4 transposed() const
    {
        Matrix4x4 c = *this;
        c.transpose();
        return c;
    }
    inline void setToIdentity()
    {
        fill(0);
        for (int i = 0; i < W; ++i)
        {
            m[i][i] = 1;
        }
    }
    inline bool isIdentity() const
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                if (i == j)
                {
                    if (m[i][j] != 1.0f)
                    {
                        return false;
                    }
                }
                else
                {
                    if (m[i][j] != 0.0f)
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }
    // bool hasInverse()
    //{
    //    return false;
    //}
    // void inverse()
    //{
    //}
    // Matrix4x4 inversed() const
    //{
    //    Matrix4x4 m;
    //    return m;
    //}
    void copyDataTo(real *values) const
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                values[i * H + j] = m[i][j];
            }
        }
    }
    real *data()
    {
        return *m;
    }

    const real *data() const
    {
        return *m;
    }
    const real *constData() const
    {
        return *m;
    }
    inline Matrix4x4 operator=(const Matrix4x4 &o)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] = o.m[i][j];
            }
        }
        return *this;
    }
    inline const real &operator()(int row, int col) const
    {
        assert(row >= 0 && row < W);
        assert(col >= 0 && col < H);
        return m[row][col];
    }
    inline real &operator()(int row, int col)
    {
        assert(row >= 0 && row < W);
        assert(col >= 0 && col < H);
        return m[row][col];
    }
    inline Matrix4x4 &operator+=(real v)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] += v;
            }
        }
        return *this;
    }
    inline Matrix4x4 &operator+=(const Matrix4x4 &o)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] += o.m[i][j];
            }
        }
        return *this;
    }
    inline Matrix4x4 &operator-=(const Matrix4x4 &o)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] -= o.m[i][j];
            }
        }
        return *this;
    }
    inline Matrix4x4 &operator-=(real v)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] -= v;
            }
        }
        return *this;
    }
    inline Matrix4x4 &operator*=(real v)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] *= v;
            }
        }
        return *this;
    }
    inline Matrix4x4 &operator/=(real v)
    {
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                m[i][j] /= v;
            }
        }
        return *this;
    }
    Matrix4x4 &operator*=(const Matrix4x4 &o);

    friend inline bool operator==(const Matrix4x4 &m1, const Matrix4x4 &m2);
    friend inline bool operator!=(const Matrix4x4 &m1, const Matrix4x4 &m2);
    friend inline bool fuzzyCompare(const Matrix4x4 &m1, const Matrix4x4 &m2);
    friend inline Matrix4x4 operator+(const Matrix4x4 &m1, real v);
    friend inline Matrix4x4 operator-(const Matrix4x4 &m1, real v);
    friend inline Matrix4x4 operator*(const Matrix4x4 &m1, real v);

    friend inline Matrix4x4 operator+(const Matrix4x4 &m1, const Matrix4x4 &m2);
    friend inline Matrix4x4 operator-(const Matrix4x4 &m1, const Matrix4x4 &m2);
    friend inline Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2);

    friend inline Matrix4x4 operator-(const Matrix4x4 &m)
    {
        Matrix4x4 result(State::Uninitialized);
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                result.m[i][j] = -m.m[i][j];
            }
        }
        return result;
    }

    friend inline Matrix4x4 operator*(real factor, const Matrix4x4 &m)
    {

        Matrix4x4 result(State::Uninitialized);
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                result.m[i][j] = m.m[i][j] * factor;
            }
        }
        return result;
    }

    friend inline Matrix4x4 operator/(const Matrix4x4 &m, real divisor)
    {
        Matrix4x4 result(State::Uninitialized);
        for (int i = 0; i < W; ++i)
        {
            for (int j = 0; j < H; ++j)
            {
                result.m[i][j] = m.m[i][j] / divisor;
            }
        }
        return result;
    }

    friend Vector4D operator*(const Vector4D &v, const Matrix4x4 &m)
    {
        return v.x() * m.row(0) + v.y() * m.row(1) + v.z() * m.row(2)
               + v.w() * m.row(3);
    }

private:
    real m[W][H] = { { 0. } };
};

inline bool operator==(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            if (m1(i, j) != m2(i, j))
            {
                return false;
            }
        }
    }
    return true;
}
inline bool operator!=(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            if (m1(i, j) != m2(i, j))
            {
                return true;
            }
        }
    }
    return false;
}
inline bool fuzzyCompare(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            if (!fuzzyCompare(m1(i, j), m2(i, j)))
            {
                return false;
            }
        }
    }
    return true;
}
inline Matrix4x4 operator+(const Matrix4x4 &m1, real v)
{
    Matrix4x4 m;
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            m(i, j) = m1(i, j) + v;
        }
    }
    return m;
}
inline Matrix4x4 operator-(const Matrix4x4 &m1, real v)
{
    Matrix4x4 m;
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            m(i, j) = m1(i, j) - v;
        }
    }
    return m;
}
inline Matrix4x4 operator*(const Matrix4x4 &m1, real v)
{
    Matrix4x4 m;
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            m(i, j) = m1(i, j) * v;
        }
    }
    return m;
}

inline Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
    Matrix4x4 m;
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            m(i, j) = Vector4D::dotProduct(m1.row(i), m2.column(j));
        }
    }
    return m;
}
inline Matrix4x4 operator+(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
    Matrix4x4 m;
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            m(i, j) = m1(i, j) + m2(i, j);
        }
    }
    return m;
}
inline Matrix4x4 operator-(const Matrix4x4 &m1, const Matrix4x4 &m2)
{
    Matrix4x4 m;
    for (int i = 0; i < Matrix4x4::W; ++i)
    {
        for (int j = 0; j < Matrix4x4::H; ++j)
        {
            m(i, j) = m1(i, j) - m2(i, j);
        }
    }
    return m;
}

} // namespace TaoMath
