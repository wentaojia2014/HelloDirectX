#pragma once

#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <type_traits>
namespace TaoMath {
using Integer = int;
class Point {
public:
    Point()
        : mX(0)
        , mY(0)
    {
    }
    Point(Integer x, Integer y)
        : mX(x)
        , mY(y)
    {
    }
    Point(const Point& o)
        : mX(o.mX)
        , mY(o.mY)
    {
    }

    bool isNull() const
    {
        return mX == 0 && mY == 0;
    }
    Integer x() const { return mX; }
    Integer y() const { return mY; }
    Integer& rx() { return mX; }
    Integer& ry() { return mY; }
    void setX(Integer x) { mX = x; }
    void setY(Integer y) { mY = y; }

    Integer manhattanLength() const
    {
        return static_cast<Integer>(std::sqrt(std::pow(x(), 2) + std::pow(y(), 2)));
    }

    template <class T, typename = std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    Point& operator+=(T add)
    {
        mX = static_cast<Integer>(std::round(mX + add));
        mY = static_cast<Integer>(std::round(mY + add));
        return *this;
    }
    Point& operator+=(const Point& o)
    {
        mX += o.mX;
        mY += o.mY;
        return *this;
    }
    template <class T, typename = std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    Point& operator-=(T dec)
    {
        mX = static_cast<Integer>(std::round(mX - dec));
        mY = static_cast<Integer>(std::round(mY - dec));
        return *this;
    }
    Point& operator-=(const Point& o)
    {
        mX -= o.mX;
        mY -= o.mY;
        return *this;
    }

    template <class T, typename = std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    Point& operator*=(T factor)
    {
        mX = static_cast<Integer>(std::round(mX * factor));
        mY = static_cast<Integer>(std::round(mY * factor));
        return *this;
    }
    template <class T, typename = std::enable_if<std::is_floating_point<T>::value>::type>
    Point& operator/=(T divisor)
    {
        mX = static_cast<Integer>(std::round(mX / divisor));
        mY = static_cast<Integer>(std::round(mY / divisor));
        return *this;
    }
    Point& operator/=(Integer divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        return *this;
    }

    static Integer dotProduct(const Point& p1, const Point& p2)
    {
        return p1.x() * p2.x() + p1.y() * p2.y();
    }

    friend bool operator==(const Point& p1, const Point& p2)
    {
        return p1.x() == p2.x() && p1.y() == p2.y();
    }
    friend bool operator!=(const Point& p1, const Point& p2)
    {
        return p1.x() != p2.x() || p1.y() != p2.y();
    }
    friend const Point operator+(const Point& p1, const Point& p2)
    {
        return Point(p1.x() + p2.x(), p1.y() + p2.y());
    }
    friend const Point operator-(const Point& p1, const Point& p2)
    {
        return Point(p1.x() - p2.x(), p1.y() - p2.y());
    }
    template <class T, class S>
    friend const Point operator/(const Point& p1, T divisor);

    template <class T, class S>
    friend const Point operator*(const Point& p1, T factor);
    template <class T, class S>
    friend const Point operator*(T factor, const Point& p1);

private:
    Integer mX, mY;
};
template <class T, class S = std::enable_if<std::is_floating_point<T>::value>::type>
const Point operator/(const Point& p1, T divisor)
{
    return Point(static_cast<Integer>(p1.x() / divisor), static_cast<Integer>(p1.x() / divisor));
}
template <class T = Integer, class S = Integer>
const Point operator/(const Point& p1, Integer divisor)
{
    assert(divisor != 0);
    return Point(static_cast<Integer>(p1.x() / divisor), static_cast<Integer>(p1.y() / divisor));
}
template <class T, class S = std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
const Point operator*(const Point& p1, T factor)
{
    return Point(static_cast<Integer>(p1.x() * factor), static_cast<Integer>(p1.y() * factor));
}

template <class T, class S = std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
const Point operator*(T factor, const Point& p1)
{
    return Point(static_cast<Integer>(p1.x() * factor), static_cast<Integer>(p1.y() * factor));
}

} // namespace TaoMath
