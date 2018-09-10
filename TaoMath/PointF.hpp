#pragma once
#include "Common.hpp"
#include "Global.h"
namespace TaoMath
{
class Point;
class TAOEXPORT PointF
{
public:
    constexpr inline PointF() : mX(0.0), mY(0.0) {}
    constexpr inline PointF(real x, real y) : mX(x), mY(y) {}
    constexpr inline PointF(const PointF &o) : mX(o.mX), mY(o.mY) {}
    Point       toPoint() const;
    inline bool isNull() const
    {
        return isZero(mX) && isZero(mY);
    }
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
    inline real &rx()
    {
        return mX;
    }
    inline real &ry()
    {
        return mY;
    }
    inline real manhattanLength() const
    {
        return std::abs(x()) + std::abs(y());
    }

    template <
        class T,
        typename = typename std::enable_if<
            std::is_integral<T>::value
            || std::is_floating_point<T>::value>::type>
    inline PointF &operator+=(T add)
    {
        mX += add;
        mY += add;
        return *this;
    }
    inline PointF &operator+=(const PointF &o)
    {
        mX += o.mX;
        mY += o.mY;
        return *this;
    }
    template <
        class T,
        typename = typename std::enable_if<
            std::is_integral<T>::value
            || std::is_floating_point<T>::value>::type>
    inline PointF &operator-=(T dec)
    {
        mX -= dec;
        mY -= dec;
        return *this;
    }
    inline PointF &operator-=(const PointF &o)
    {
        mX -= o.mX;
        mY -= o.mY;
        return *this;
    }

    template <
        class T,
        typename = typename std::enable_if<
            std::is_integral<T>::value
            || std::is_floating_point<T>::value>::type>
    inline PointF &operator*=(T factor)
    {
        mX *= factor;
        mY *= factor;
        return *this;
    }
    template <
        class T,
        typename
        = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline PointF &operator/=(T divisor)
    {
        mX /= divisor;
        mY /= divisor;
        return *this;
    }
    inline PointF &operator/=(int divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        return *this;
    }

    constexpr inline static real dotProduct(const PointF &p1, const PointF &p2)
    {
        return p1.x() * p2.x() + p1.y() * p2.y();
    }

    friend inline bool operator==(const PointF &p1, const PointF &p2)
    {
        return fuzzyCompare(p1.x(), p2.x()) && fuzzyCompare(p1.y(), p2.y());
    }
    friend inline bool operator!=(const PointF &p1, const PointF &p2)
    {
        return !fuzzyCompare(p1.x(), p2.x()) || !fuzzyCompare(p1.y(), p2.y());
    }
    friend constexpr inline const PointF
    operator+(const PointF &p1, const PointF &p2)
    {
        return PointF(p1.x() + p2.x(), p1.y() + p2.y());
    }
    friend constexpr inline const PointF
    operator-(const PointF &p1, const PointF &p2)
    {
        return PointF(p1.x() - p2.x(), p1.y() - p2.y());
    }

    template <
        class T,
        class S
        = typename std::enable_if<std::is_floating_point<T>::value>::type>
    friend constexpr inline PointF operator/(const PointF &p1, T divisor)
    {
        return PointF(p1.x() / divisor, p1.x() / divisor);
    }
    template <class T = int, class S = int>
    friend inline const PointF operator/(const PointF &p1, int divisor)
    {
        assert(divisor != 0);
        return PointF(p1.x() / divisor, p1.y() / divisor);
    }
    template <
        class T,
        class S = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    friend constexpr inline PointF operator*(const PointF &p1, T factor)
    {
        return PointF(p1.x() * factor, p1.y() * factor);
    }

    template <
        class T,
        class S = typename std::enable_if<
            std::is_floating_point<T>::value
            || std::is_integral<T>::value>::type>
    friend constexpr inline PointF operator*(T factor, const PointF &p1)
    {
        return PointF(p1.x() * factor, p1.y() * factor);
    }

private:
    real mX, mY;
};

} // namespace TaoMath
