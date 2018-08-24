#pragma once
#include "Global.h"
#include "Common.hpp"

namespace TaoMath {

class TAOEXPORT Point {
public:
    constexpr inline Point()
        : mX(0)
        , mY(0)
    {
    }
    constexpr inline  Point(Integer x, Integer y)
        : mX(x)
        , mY(y)
    {
    }
    constexpr inline Point(const Point& o)
        : mX(o.mX)
        , mY(o.mY)
    {
    }

    inline bool isNull() const
    {
        return mX == 0 && mY == 0;
    }
    constexpr inline Integer x() const { return mX; }
    constexpr inline Integer y() const { return mY; }
    inline Integer& rx() { return mX; }
    inline Integer& ry() { return mY; }
    inline void setX(Integer x) { mX = x; }
    inline void setY(Integer y) { mY = y; }

    inline Integer manhattanLength() const
    {
        return static_cast<Integer>(std::sqrt(std::pow(x(), 2) + std::pow(y(), 2)));
    }

    template <class T, typename = typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    inline Point& operator+=(T add)
    {
        mX = static_cast<Integer>(std::round(mX + add));
        mY = static_cast<Integer>(std::round(mY + add));
        return *this;
    }
    inline Point& operator+=(const Point& o)
    {
        mX += o.mX;
        mY += o.mY;
        return *this;
    }
    template <class T, typename = typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    inline Point& operator-=(T dec)
    {
        mX = static_cast<Integer>(std::round(mX - dec));
        mY = static_cast<Integer>(std::round(mY - dec));
        return *this;
    }
    inline Point& operator-=(const Point& o)
    {
        mX -= o.mX;
        mY -= o.mY;
        return *this;
    }

    template <class T, typename = typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    inline Point& operator*=(T factor)
    {
        mX = static_cast<Integer>(std::round(mX * factor));
        mY = static_cast<Integer>(std::round(mY * factor));
        return *this;
    }
    template <class T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
    inline Point& operator/=(T divisor)
    {
        mX = static_cast<Integer>(std::round(mX / divisor));
        mY = static_cast<Integer>(std::round(mY / divisor));
        return *this;
    }
    inline Point& operator/=(Integer divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        return *this;
    }

    constexpr inline static Integer dotProduct(const Point& p1, const Point& p2)
    {
        return p1.x() * p2.x() + p1.y() * p2.y();
    }

    friend constexpr inline bool operator==(const Point& p1, const Point& p2)
    {
        return p1.x() == p2.x() && p1.y() == p2.y();
    }
    friend constexpr inline bool operator!=(const Point& p1, const Point& p2)
    {
        return p1.x() != p2.x() || p1.y() != p2.y();
    }
    friend constexpr inline const Point operator+(const Point& p1, const Point& p2)
    {
        return Point(p1.x() + p2.x(), p1.y() + p2.y());
    }
    friend constexpr inline const Point operator-(const Point& p1, const Point& p2)
    {
        return Point(p1.x() - p2.x(), p1.y() - p2.y());
    }

    template <class T, class S = typename std::enable_if<std::is_floating_point<T>::value>::type>
    friend constexpr inline const Point operator/(const Point& p1, T divisor)
    {
        return Point(static_cast<Integer>(p1.x() / divisor), static_cast<Integer>(p1.x() / divisor));
    }
    template <class T = Integer, class S = Integer>
    friend inline const Point operator/(const Point& p1, Integer divisor)
    {
        assert(divisor != 0);
        return Point(static_cast<Integer>(p1.x() / divisor), static_cast<Integer>(p1.y() / divisor));
    }
    template <class T, class S = typename std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
    friend constexpr inline const Point operator*(const Point& p1, T factor)
    {
        return Point(static_cast<Integer>(p1.x() * factor), static_cast<Integer>(p1.y() * factor));
    }

    template <class T, class S = typename std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
    friend constexpr inline const Point operator*(T factor, const Point& p1)
    {
        return Point(static_cast<Integer>(p1.x() * factor), static_cast<Integer>(p1.y() * factor));
    }


private:
    Integer mX, mY;
};

} // namespace TaoMath
