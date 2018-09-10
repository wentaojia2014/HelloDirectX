#pragma once
#include "Common.hpp"
#include "Global.h"
#include "TaoMathFwd"
namespace TaoMath
{

class TAOEXPORT Vector3D
{
public:
    constexpr inline Vector3D() : mX(0), mY(0), mZ(0) {}
    constexpr inline Vector3D(real x, real y, real z) : mX(x), mY(y), mZ(z) {}
    constexpr inline Vector3D(const Vector3D &o) : mX(o.mX), mY(o.mY), mZ(o.mZ)
    {
    }

    Vector3D(const Vector2D &o);
    Vector3D(const Vector4D &o);
    Vector3D(const Point &o);
    Vector3D(const PointF &o);

    constexpr inline real x() const
    {
        return mX;
    }
    constexpr inline real y() const
    {
        return mY;
    }
    constexpr inline real z() const
    {
        return mZ;
    }

    inline void setX(real x)
    {
        mX = x;
    }
    inline void setY(real y)
    {
        mY = y;
    }
    inline void setZ(real z)
    {
        mZ = z;
    }

    Point    toPoint() const;
    PointF   toPointF() const;
    Vector2D toVector2D() const;
    Vector4D toVector4D() const;

    bool isNull() const;
    real length() const;
    real lengthSquared() const;

    void     normalize();
    Vector3D normalized() const;

    inline Vector3D &operator+=(const Vector3D &o)
    {
        mX += o.mX;
        mY += o.mY;
        mZ += o.mZ;
        return *this;
    }

    inline Vector3D &operator-=(const Vector3D &o)
    {
        mX -= o.mX;
        mY -= o.mY;
        mZ -= o.mZ;
        return *this;
    }

    inline Vector3D &operator*=(const Vector3D &o)
    {
        mX *= o.mX;
        mY *= o.mY;
        mZ *= o.mZ;
        return *this;
    }

    inline Vector3D &operator/=(const Vector3D &o)
    {
        mX /= o.mX;
        mY /= o.mY;
        mZ /= o.mZ;
        return *this;
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector3D &operator+=(T v)
    {
        mX += v;
        mY += v;
        mZ += v;
        return *this;
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector3D &operator-=(T v)
    {
        mX -= v;
        mY -= v;
        mZ -= v;
        return *this;
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector3D &operator*=(T v)
    {
        mX *= v;
        mY *= v;
        mZ *= v;
        return *this;
    }

    template <
        typename T,
        typename
        = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline Vector3D &operator/=(T divisor)
    {
        mX /= divisor;
        mY /= divisor;
        mZ /= divisor;
        return *this;
    }

    inline Vector3D &operator/=(int divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        mZ /= divisor;
        return *this;
    }

    real distanceToPoint(const Vector3D &point) const;
    real distanceToPlane(const Vector3D &plane, const Vector3D &normal) const;
    real distanceToPlane(
        const Vector3D &plane1,
        const Vector3D &plane2,
        const Vector3D &plane3) const;
    real distanceToLine(const Vector3D &point, const Vector3D &direction) const;

    static real     dotProduct(const Vector3D &v1, const Vector3D &v2);
    static Vector3D crossProduct(const Vector3D &v1, const Vector3D &v2);
    static Vector3D normal(const Vector3D &v1, const Vector3D &v2);
    static Vector3D
    normal(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3);

    friend inline bool operator==(const Vector3D &v1, const Vector3D &v2);
    friend inline bool operator!=(const Vector3D &v1, const Vector3D &v2);
    friend inline bool fuzzyCompare(const Vector3D &v1, const Vector3D &v2);

    friend inline constexpr const Vector3D
    operator+(const Vector3D &v1, const Vector3D &v2);
    friend inline constexpr const Vector3D
    operator-(const Vector3D &v1, const Vector3D &v2);
    friend inline constexpr const Vector3D
    operator*(const Vector3D &v1, const Vector3D &v2);
    friend inline constexpr const Vector3D
    operator/(const Vector3D &v1, const Vector3D &v2);

    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    friend constexpr const Vector3D operator*(const Vector3D &v, T factor)
    {
        return Vector3D(v.x() * factor, v.y() * factor, v.z() * factor);
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    friend constexpr const Vector3D operator*(T factor, const Vector3D &v)
    {
        return Vector3D(v.x() * factor, v.y() * factor, v.z() * factor);
    }

    template <
        typename T,
        typename
        = typename std::enable_if<std::is_floating_point<T>::value>::type>
    friend constexpr const Vector3D operator/(const Vector3D &v, T divisor)
    {
        return Vector3D(v.x() / divisor, v.y() / divisor, v.z() / divisor);
    }

    template <typename T = int, typename S = int>
    friend const Vector3D operator/(const Vector3D &v, int divisor)
    {
        assert(divisor != 0);
        return Vector3D(v.x() / divisor, v.y() / divisor, v.z() / divisor);
    }

private:
    real mX, mY, mZ;
};

bool operator==(const Vector3D &v1, const Vector3D &v2)
{
    return fuzzyCompare(v1.x(), v2.x()) && fuzzyCompare(v1.y(), v2.y())
           && fuzzyCompare(v1.z(), v2.z());
}
bool operator!=(const Vector3D &v1, const Vector3D &v2)
{
    return !fuzzyCompare(v1.x(), v2.x()) || !fuzzyCompare(v1.y(), v2.y())
           || !fuzzyCompare(v1.z(), v2.z());
}
bool fuzzyCompare(const Vector3D &v1, const Vector3D &v2)
{
    return fuzzyCompare(v1.x(), v2.x()) && fuzzyCompare(v1.y(), v2.y())
           && fuzzyCompare(v1.z(), v2.z());
}

constexpr inline const Vector3D
operator+(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}
constexpr inline const Vector3D
operator-(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}
constexpr inline const Vector3D
operator*(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}
constexpr inline const Vector3D
operator/(const Vector3D &v1, const Vector3D &v2)
{
    return Vector3D(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

} // namespace TaoMath
