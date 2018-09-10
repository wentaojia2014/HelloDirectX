#pragma once
#include "Common.hpp"
#include "Global.h"
#include "TaoMathFwd"
namespace TaoMath
{
class TAOEXPORT Vector4D
{
public:
    constexpr inline Vector4D() : mX(0), mY(0), mZ(0), mW(0) {}
    constexpr inline Vector4D(real x, real y, real z, real w)
        : mX(x), mY(y), mZ(z), mW(w)
    {
    }
    constexpr inline Vector4D(const Vector4D &o)
        : mX(o.x()), mY(o.y()), mZ(o.z()), mW(o.w())
    {
    }

    Vector4D(const Vector2D &o);
    Vector4D(const Vector3D &o);
    Vector4D(const Point &o);
    Vector4D(const PointF &o);

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
    constexpr inline real w() const
    {
        return mW;
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
    inline void setW(real w)
    {
        mW = w;
    }

    Point    toPoint() const;
    PointF   toPointF() const;
    Vector2D toVector2D() const;
    Vector3D toVector3D() const;

    bool     isNull() const;
    real     length() const;
    real     lengthSquared() const;
    Vector4D normalized() const;
    void     normalize();

    inline Vector4D &operator+=(const Vector4D &o)
    {
        mX += o.mX;
        mY += o.mY;
        mZ += o.mZ;
        mW += o.mW;
        return *this;
    }
    inline Vector4D &operator-=(const Vector4D &o)
    {
        mX -= o.mX;
        mY -= o.mY;
        mZ -= o.mZ;
        mW -= o.mW;
        return *this;
    }
    inline Vector4D &operator*=(const Vector4D &o)
    {
        mX *= o.mX;
        mY *= o.mY;
        mZ *= o.mZ;
        mW *= o.mW;
        return *this;
    }
    inline Vector4D &operator/=(const Vector4D &o)
    {
        mX /= o.mX;
        mY /= o.mY;
        mZ /= o.mZ;
        mW /= o.mW;
        return *this;
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector4D &operator+=(T v)
    {
        mX += v;
        mY += v;
        mZ += v;
        mW += v;
        return *this;
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector4D &operator-=(T v)
    {
        mX -= v;
        mY -= v;
        mZ -= v;
        mW -= v;
        return *this;
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    inline Vector4D &operator*=(T v)
    {
        mX *= v;
        mY *= v;
        mZ *= v;
        mW *= v;
        return *this;
    }

    template <
        typename T,
        typename
        = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline Vector4D &operator/=(T divisor)
    {
        mX /= divisor;
        mY /= divisor;
        mZ /= divisor;
        mW /= divisor;
        return *this;
    }

    inline Vector4D &operator/=(int divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        mZ /= divisor;
        mW /= divisor;
        return *this;
    }

    static real dotProduct(const Vector4D &v1, const Vector4D &v2);

    friend inline bool operator==(const Vector4D &v1, const Vector4D &v2);
    friend inline bool operator!=(const Vector4D &v1, const Vector4D &v2);
    friend inline bool fuzzyCompare(const Vector4D &v1, const Vector4D &v2);

    friend inline constexpr const Vector4D
    operator+(const Vector4D &v1, const Vector4D &v2);
    friend inline constexpr const Vector4D
    operator-(const Vector4D &v1, const Vector4D &v2);
    friend inline constexpr const Vector4D
    operator*(const Vector4D &v1, const Vector4D &v2);
    friend inline constexpr const Vector4D
    operator/(const Vector4D &v1, const Vector4D &v2);

    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    friend const Vector4D operator*(const Vector4D &v, T factor)
    {
        return Vector4D(
            v.x() * factor, v.y() * factor, v.z() * factor, v.w() * factor);
    }
    template <
        typename T,
        typename = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    friend const Vector4D operator*(T factor, const Vector4D &v)
    {
        return Vector4D(
            v.x() * factor, v.y() * factor, v.z() * factor, v.w() * factor);
    }

    template <
        typename T,
        typename
        = typename std::enable_if<std::is_floating_point<T>::value>::type>
    friend const Vector4D operator/(const Vector4D &v, T divisor)
    {
        return Vector4D(
            v.x() / divisor, v.y() / divisor, v.z() / divisor, v.w() / divisor);
    }

    template <typename T = int, typename S = int>
    friend const Vector4D operator/(const Vector4D &v, int divisor)
    {
        assert(divisor != 0);
        return Vector4D(
            v.x() / divisor, v.y() / divisor, v.z() / divisor, v.w() / divisor);
    }

private:
    real mX, mY, mZ, mW;
};

inline bool operator==(const Vector4D &v1, const Vector4D &v2)
{
    return fuzzyCompare(v1.x(), v2.x()) && fuzzyCompare(v1.y(), v2.y())
           && fuzzyCompare(v1.z(), v2.z()) && fuzzyCompare(v1.w(), v2.w());
}
inline bool operator!=(const Vector4D &v1, const Vector4D &v2)
{
    return !fuzzyCompare(v1.x(), v2.x()) || !fuzzyCompare(v1.y(), v2.y())
           || !fuzzyCompare(v1.z(), v2.z()) || !fuzzyCompare(v1.w(), v2.w());
}
inline bool fuzzyCompare(const Vector4D &v1, const Vector4D &v2)
{
    return fuzzyCompare(v1.x(), v2.x()) && fuzzyCompare(v1.y(), v2.y())
           && fuzzyCompare(v1.z(), v2.z()) && fuzzyCompare(v1.w(), v2.w());
}

constexpr inline const Vector4D
operator+(const Vector4D &v1, const Vector4D &v2)
{
    return Vector4D(
        v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z(), v1.w() + v2.w());
}
constexpr inline const Vector4D
operator-(const Vector4D &v1, const Vector4D &v2)
{
    return Vector4D(
        v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z(), v1.w() - v2.w());
}
constexpr inline const Vector4D
operator*(const Vector4D &v1, const Vector4D &v2)
{
    return Vector4D(
        v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z(), v1.w() * v2.w());
}
constexpr inline const Vector4D
operator/(const Vector4D &v1, const Vector4D &v2)
{
    return Vector4D(
        v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z(), v1.w() / v2.w());
}

} // namespace TaoMath
