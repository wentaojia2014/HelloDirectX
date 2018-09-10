#pragma once
#include "Common.hpp"
#include "Global.h"

namespace TaoMath
{
class Point;
class PointF;
class Vector3D;
class Vector4D;
class TAOEXPORT Vector2D
{
public:
    constexpr inline Vector2D() : mX(0), mY(0) {}
    constexpr inline Vector2D(real x, real y) : mX(x), mY(y) {}
    constexpr inline Vector2D(const Vector2D &o) : mX(o.mX), mY(o.mY) {}

    Vector2D(const Point &o);
    Vector2D(const PointF &o);
    Vector2D(const Vector3D &o);
    Vector2D(const Vector4D &o);

    constexpr inline real x() const
    {
        return mX;
    }
    constexpr inline real y() const
    {
        return mY;
    }
    inline void setX(real x)
    {
        mX = x;
    }
    inline void setY(real y)
    {
        mY = y;
    }

    real distanceToLine(const Vector2D &point, const Vector2D &direction) const;
    real distanceToPoint(const Vector2D &point) const;
    bool isNull() const;
    real length() const;
    real lengthSquared() const;
    void normalize();
    Vector2D normalized() const;

    Point    toPoint() const;
    PointF   toPointF() const;
    Vector3D toVector3D() const;
    Vector4D toVector4D() const;

    inline Vector2D &operator+=(const Vector2D &o)
    {
        mX += o.mX;
        mY += o.mY;
        return *this;
    }
    inline Vector2D &operator-=(const Vector2D &o)
    {
        mX -= o.mX;
        mY -= o.mY;
        return *this;
    }
    inline Vector2D &operator*=(const Vector2D &o)
    {
        mX *= o.mX;
        mY *= o.mY;
        return *this;
    }
    inline Vector2D &operator/=(const Vector2D &o)
    {
        mX /= o.mX;
        mY /= o.mY;
        return *this;
    }

    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector2D &operator+=(T v)
    {
        mX += v;
        mY += v;
        return *this;
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector2D &operator-=(T v)
    {
        mX -= v;
        mY -= v;
        return *this;
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector2D &operator*=(T v)
    {
        mX *= v;
        mY *= v;
        return *this;
    }
    template <
        typename T,
        typename
        = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline Vector2D &operator/=(T v)
    {
        mX /= v;
        mY /= v;
        return *this;
    }
    inline Vector2D &operator/=(int v)
    {
        assert(v != 0);
        mX /= v;
        mY /= v;
        return *this;
    }

    inline static real dotProduct(const Vector2D &v1, const Vector2D &v2)
    {
        return v1.x() * v2.x() + v1.y() * v2.y();
    }

    friend inline bool operator==(const Vector2D &v1, const Vector2D &v2);
    friend inline bool operator!=(const Vector2D &v1, const Vector2D &v2);
    friend inline bool fuzzyCompare(const Vector2D &v1, const Vector2D &v2);

    friend constexpr inline const Vector2D
    operator+(const Vector2D &v1, const Vector2D &v2);
    friend constexpr inline const Vector2D
    operator-(const Vector2D &v1, const Vector2D &v2);
    friend constexpr inline const Vector2D
    operator*(const Vector2D &v1, const Vector2D &v2);
    friend constexpr inline const Vector2D
    operator/(const Vector2D &v1, const Vector2D &v2);

    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    friend constexpr const Vector2D operator*(const Vector2D &v, T factor)
    {
        return Vector2D(v.x() * factor, v.y() * factor);
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    friend constexpr const Vector2D operator*(T factor, const Vector2D &v)
    {
        return Vector2D(v.x() * factor, v.y() * factor);
    }

    template <
        typename T,
        typename
        = typename std::enable_if<std::is_floating_point<T>::value>::type>
    friend constexpr const Vector2D operator/(const Vector2D &v, T divisor)
    {
        return Vector2D(v.x() / divisor, v.y() / divisor);
    }

    template <typename T = int, typename S = int>
    friend const Vector2D operator/(const Vector2D &v, int divisor)
    {
        assert(divisor != 0);
        return Vector2D(v.x() / divisor, v.y() / divisor);
    }

private:
    real mX, mY;
};

inline bool operator==(const Vector2D &v1, const Vector2D &v2)
{
    return fuzzyCompare(v1.x(), v2.x()) && fuzzyCompare(v1.y(), v2.y());
}
inline bool operator!=(const Vector2D &v1, const Vector2D &v2)
{
    return !fuzzyCompare(v1.x(), v2.x()) || !fuzzyCompare(v1.y(), v2.y());
}
inline bool fuzzyCompare(const Vector2D &v1, const Vector2D &v2)
{
    return fuzzyCompare(v1.x(), v2.x()) && fuzzyCompare(v1.y(), v2.y());
}

constexpr inline const Vector2D
operator+(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x() + v2.x(), v1.y() + v2.y());
}
constexpr inline const Vector2D
operator-(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x() - v2.x(), v1.y() - v2.y());
}
constexpr inline const Vector2D
operator*(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x() * v2.x(), v1.y() * v2.y());
}
constexpr inline const Vector2D
operator/(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x() / v2.x(), v1.y() / v2.y());
}

} // namespace TaoMath
