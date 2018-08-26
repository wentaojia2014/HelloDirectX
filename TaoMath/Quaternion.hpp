#pragma once
#include "Common.hpp"
#include "Global.h"

#include "MatrixGeneric.hpp"
#include "Vector3D.hpp"
#include "Vector4D.hpp"

namespace TaoMath {

class TAOEXPORT Quaternion {
public:
    constexpr inline Quaternion()
        : mX(0)
        , mY(0)
        , mZ(0)
        , mScalar(0)
    {
    }
    constexpr inline Quaternion(real scalar, real x, real y, real z)
        : mX(x)
        , mY(y)
        , mZ(z)
        , mScalar(scalar)
    {
    }
    Quaternion(real scalar, const Vector3D& v);
    Quaternion(const Vector4D& v);

    real scalar() const { return mScalar; }
    real x() const { return mX; }
    real y() const { return mY; }
    real z() const { return mZ; }
    Vector3D vector() const;

    void setScalar(real scalar) { mScalar = scalar; }
    void setX(real x) { mX = x; }
    void setY(real y) { mY = y; }
    void setZ(real z) { mZ = z; }

    void setVector(const Vector3D& vector);
    void setVector(real x, real y, real z);

    Vector4D toVector4D() const;
    void getAxisAndAngle(Vector3D& axis, real& angle) const;
    void getAxisAndAngle(real& x, real& y, real& z, real& angle) const;

    Vector3D toEulerAngles() const;
    void getEulerAngles(real& pitch, real& yaw, real& roll) const;

    Matrix3x3 toRotationMatrix () const;
    static Quaternion fromRotationMatrix (const Matrix3x3 &rot3x3);

    void getAxes(Vector3D& xAxis, Vector3D& yAxis, Vector3D& zAxis) const;

    bool isNull() const;
    bool isIdentity() const;
    void setToIdentity ();
    real length() const;
    real lengthSquared() const;

    Quaternion normalized() const;
    void normalize();
    Quaternion inverted() const;
    Quaternion conjugated() const;
    Vector3D rotatedVector(const Vector3D& v) const;

    static Quaternion fromAxisAndAngle(real x, real y, real z, real angle);
    static Quaternion fromAxisAndAngle(const Vector3D& axis, real angle);

    static Quaternion fromEulerAngles(real pitch, real yaw, real roll);
    static Quaternion fromEulerAngles(const Vector3D& eulerAngles);

    static Quaternion fromAxes(const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis);
    static Quaternion fromDirection(const Vector3D& direction, const Vector3D& up);
    static Quaternion rotationTo(const Vector3D& from, const Vector3D& to);
    static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, real t);
    static Quaternion nlerp(const Quaternion& q1, const Quaternion& q2, real t);

    static real dotProduct(const Quaternion& q1, const Quaternion& q2);
    Quaternion& operator+=(const Quaternion& q);
    Quaternion& operator-=(const Quaternion& q);
    Quaternion& operator*=(const Quaternion& q);

    template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
    inline Quaternion& operator*=(T v)
    {
        mX *= v;
        mY *= v;
        mZ *= v;
        mScalar *= v;
        return *this;
    }

    template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline Quaternion& operator/=(T divisor)
    {
        mX /= divisor;
        mY /= divisor;
        mZ /= divisor;
        mScalar /= divisor;
        return *this;
    }
    inline Quaternion& operator/=(int divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        mZ /= divisor;
        mScalar /= divisor;
        return *this;
    }

    friend constexpr inline bool operator==(const Quaternion& q1, const Quaternion& q2);
    friend constexpr inline bool operator!=(const Quaternion& q1, const Quaternion& q2);
    friend inline bool fuzzyCompare(const Quaternion& q1, const Quaternion& q2);

    friend constexpr inline const Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
    friend constexpr inline const Quaternion operator-(const Quaternion& q1, const Quaternion& q2);
    friend constexpr inline const Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

    friend inline const Quaternion operator-(const Quaternion& q1);

    template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
    friend constexpr Quaternion operator*(const Quaternion& v, T factor)
    {
        return Quaternion(v.scalar() * factor, v.x() * factor, v.y() * factor, v.z() * factor);
    }
    template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
    friend constexpr Quaternion operator*(T factor, const Quaternion& v)
    {
        return Quaternion(v.scalar() * factor, v.x() * factor, v.y() * factor, v.z() * factor);
    }

    template <typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    friend constexpr Quaternion operator/(const Quaternion& v, T divisor)
    {
        return Quaternion(v.scalar() / divisor, v.x() / divisor, v.y() / divisor, v.z() / divisor);
    }

    template <typename T = int, typename S = int>
    friend Quaternion operator/(const Quaternion& v, int divisor)
    {
        assert(divisor != 0);
        return Quaternion(v.scalar() / divisor, v.x() / divisor, v.y() / divisor, v.z() / divisor);
    }


private:
    real mX, mY, mZ, mScalar;
};
constexpr inline bool operator==(const Quaternion& q1, const Quaternion& q2)
{
    return q1.mScalar == q2.mScalar && q1.mX == q2.mX && q1.mY == q2.mY && q1.mZ == q2.mZ;
}
constexpr inline bool operator!=(const Quaternion& q1, const Quaternion& q2)
{
    return q1.mScalar != q2.mScalar || q1.mX != q2.mX || q1.mY != q2.mY || q1.mZ != q2.mZ;
}
inline bool fuzzyCompare(const Quaternion& q1, const Quaternion& q2)
{
    return fuzzyCompare(q1.mScalar, q2.mScalar) && fuzzyCompare(q1.mX, q2.mX) && fuzzyCompare(q1.mY, q2.mY) && fuzzyCompare(q1.mZ, q2.mZ);
}

constexpr inline const Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.mScalar + q2.mScalar, q1.mX + q2.mX, q1.mY + q2.mY, q1.mZ + q2.mZ);
}
constexpr inline const Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.mScalar - q2.mScalar, q1.mX - q2.mX, q1.mY - q2.mY, q1.mZ - q2.mZ);
}
constexpr inline const Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
    return Quaternion(q1.mScalar * q2.mScalar, q1.mX * q2.mX, q1.mY * q2.mY, q1.mZ * q2.mZ);
}
inline const Quaternion operator-(const Quaternion& q1)
{
    return Quaternion(-q1.scalar(), -q1.x(), -q1.y(), -q1.z());
}

}
