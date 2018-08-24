#include "Matrix4x4.hpp"
#include "Vector4D.hpp"
namespace TaoMath {
inline const Vector4D Matrix4x4::row(int r) const
{
    assert(0 <= r && r < W);
    return Vector4D(m[r][0], m[r][1], m[r][2], m[r][3]);
}

void Matrix4x4::setRow (int r, const Vector4D & v) { 
    assert (0 <= r && r < W);
    m[r][0] = v.x ();
    m[r][1] = v.y ();
    m[r][2] = v.z ();
    m[r][3] = v.w ();
}

inline const Vector4D Matrix4x4::column(int c) const
{
    assert(0 <= c && c < H);
    return Vector4D(m[0][c], m[1][c], m[2][c], m[3][c]);
}

void Matrix4x4::setColumn (int c, const Vector4D & v) { 
    assert (0 <= c && c < H);
    m[0][c] = v.x ();
    m[1][c] = v.y ();
    m[2][c] = v.z ();
    m[3][c] = v.w ();
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& o)
{
    Matrix4x4 c = *this;
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            m[i][j] = Vector4D::dotProduct(c.row(i), o.column(j));
        }
    }
    return *this;
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 m;
    for (int i = 0; i < Matrix4x4::W; ++i) {
        for (int j = 0; j < Matrix4x4::H; ++j) {
            m (i, j) = m1 (i, j) + m2 (i, j);
        }
    }
    return m;
}

Vector4D operator*(const Vector4D & v, const Matrix4x4 & m) {
    return v.x () * m.row (0) + v.y () * m.row (1) + v.z () * m.row (2) + v.w () * m.row (3);
}

}
