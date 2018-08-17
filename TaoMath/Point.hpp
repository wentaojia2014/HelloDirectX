#pragma once

#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <type_traits>
namespace TaoMath {
class Point {
public:
    Point()
        : mX(0)
        , mY(0)
    {
    }
    Point(int x, int y)
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
    int x() const { return mX; }
    int y() const { return mY; }
    int& rx() { return mX; }
    int& ry() { return mY; }
    void setX(int x) { mX = x; }
    void setY(int y) { mY = y; }

    int manhattanLength() const
    {
        return static_cast<int>(std::sqrt(std::pow(x(), 2) + std::pow(y(), 2)));
    }

    template <class T, typename = std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    Point& operator+=(T add)
    {
        mX = std::round(mX + add);
        mY = std::round(mY + add);
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
        mX = std::round(mX - dec);
        mY = std::round(mY - dec);
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
        mX = std::round(mX * factor);
        mY = std::round(mY * factor);
        return *this;
    }
    template <class T, typename = std::enable_if<std::is_floating_point<T>::value>::type>
    Point& operator/=(T divisor)
    {
        mX = std::round(mX / divisor);
        mY = std::round(mY / divisor);
        return *this;
    }
    Point& operator/=(int divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        return *this;
    }

    static int dotProduct(const Point& p1, const Point& p2)
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
    int mX, mY;
};
template <class T, class S = std::enable_if<std::is_floating_point<T>::value>::type>
const Point operator/(const Point& p1, T divisor)
{
    return Point(p1.x() / divisor, p1.x() / divisor);
}
template <class T = int, class S = int>
const Point operator/(const Point& p1, int divisor)
{
    assert(divisor != 0);
    return Point(p1.x() / divisor, p1.y() / divisor);
}
template <class T, class S = std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
const Point operator*(const Point& p1, T factor)
{
    return Point(p1.x() * factor, p1.y() * factor);
}

template <class T, class S = std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
const Point operator*(T factor, const Point& p1)
{
    return Point(p1.x() * factor, p1.y() * factor);
}

} // namespace TaoMath
