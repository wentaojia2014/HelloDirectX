#pragma once

#include "Global.h"
#include <cmath>
#include <numeric>
#include <limits>
#include <cassert>
#include <type_traits>
namespace TaoMath
{
class TAOMATH_EXPORT Point
{
  public:
    Point() {}
    Point(int x, int y) : mX(x), mY(y) {}
    bool isNull() const
    {
        return mX == 0 && mY == 0;
    }
    int x() const { return mX; }
    int y() const { return mY; }
    int manhattanLength() const
    {
        return static_cast<int>(std::sqrt(std::pow(x(), 2) + std::pow(y(), 2)));
    }
    int &rx() { return mX; }
    int &ry() { return mY; }

    template <class T, typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type = 0>
    Point &operator+=(T add)
    {
        mX = std::round(mX + add);
        mY = std::round(mY + add);
        return *this;
    }
    Point &operator+=(const Point &o)
    {
        mX += o.mX;
        mY += o.mY;
        return *this;
    }
    template <class T, typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type = 0>
    Point &operator-=(T dec)
    {
        mX = std::round(mX - dec);
        mY = std::round(mY - dec);
        return *this;
    }
    Point &operator-=(const Point &o)
    {
        mX -= o.mX;
        mY -= o.mY;
        return *this;
    }

    template <class T, typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type = 0>
    Point &operator*=(T factor)
    {
        mX = std::round( mX * factor);
        mY = std::round( mY * factor);
        return *this;
    }
    template <class T, typename std::enable_if<std::is_floating_point<T>::value>::type = 0>
    Point &operator/=(T divisor)
    {
        mX = std::round(mX / divisor);
        mY = std::round(mY / divisor);
        return *this;
    }
    Point &operator/=(int divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        return *this;
    }

    static int dotProduct(const Point &p1, const Point &p2)
    {
        return p1.x() * p2.x() + p2.y() * p2.y();
    }
    
    friend bool operator==(const Point &p1, const Point &p2)
    {
        return p1.x() == p2.x() && p1.y() == p2.y();
    }
    friend bool operator!=(const Point &p1, const Point &p2)
    {
        return p1.x() != p2.x() || p1.y() != p2.y();
    }
    friend const Point operator+(const Point &p1, const Point &p2)
    {
        return Point(p1.x() + p2.x(), p1.y() + p2.y());
    }
    friend const Point operator-(const Point &p1, const Point &p2)
    {
        return Point(p1.x() - p2.x(), p1.y() - p2.y());
    }
    //     friend const Point operator* (const Point &p1, const Point &p2) {
    //     return Point(p1.x() + p2.x(), p1.y() + p2.y());
    // }
  private:
    int mX, mY;
};

} // namespace TaoMath