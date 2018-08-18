#pragma once
#include "Point.hpp"

#include <algorithm>

namespace TaoMath {

using real = double;

template <class T,
    class S = std::enable_if<std::is_floating_point<T>::value>::type>
bool isZero(T v)
{
    return std::abs(v) < std::numeric_limits<T>::epsilon();
}

bool fuzzyCompare(float p1, float p2)
{
    return std::abs(p1 - p2) * 100000.0f <= std::min(std::abs(p1), std::abs(p2));
}
bool fuzzyCompare(double p1, double p2)
{
    return std::abs(p1 - p2) * 1000000000000. <= std::min(std::abs(p1), std::abs(p2));
}

class PointF {
public:
    PointF()
        : mX(0.0)
        , mY(0.0)
    {
    }
    PointF(real x, real y)
        : mX(x)
        , mY(y)
    {
    }
    PointF(const PointF& o)
        : mX(o.mX)
        , mY(o.mY)
    {
    }
    Point toPoint() const
    {
        return Point(mX, mY);
    }
    bool isNull() const { return isZero(mX) && isZero(mY); }
    real x() const { return mX; }
    real y() const { return mY; }
    void setX(real x) { mX = x; }
    void setY(real y) { mY = y; }
    real& rx() { return mX; }
    real& ry() { return mY; }
    real manhattanLength() const { return std::abs(x()) + std::abs(y()); }

    template <class T,
        typename = std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    PointF& operator+=(T add)
    {
        mX += add;
        mY += add;
        return *this;
    }
    PointF& operator+=(const PointF& o)
    {
        mX += o.mX;
        mY += o.mY;
        return *this;
    }
    template <class T,
        typename = std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    PointF& operator-=(T dec)
    {
        mX -= dec;
        mY -= dec;
        return *this;
    }
    PointF& operator-=(const PointF& o)
    {
        mX -= o.mX;
        mY -= o.mY;
        return *this;
    }

    template <class T,
        typename = std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value>::type>
    PointF& operator*=(T factor)
    {
        mX *= factor;
        mY *= factor;
        return *this;
    }
    template <class T,
        typename = std::enable_if<std::is_floating_point<T>::value>::type>
    PointF& operator/=(T divisor)
    {
        mX /= divisor;
        mY /= divisor;
        return *this;
    }
    PointF& operator/=(int divisor)
    {
        assert(divisor != 0);
        mX /= divisor;
        mY /= divisor;
        return *this;
    }

    static real dotProduct(const PointF& p1, const PointF& p2)
    {
        return p1.x() * p2.x() + p1.y() * p2.y();
    }

    friend bool operator==(const PointF& p1, const PointF& p2)
    {
        return fuzzyCompare(p1.x(), p2.x()) && fuzzyCompare(p1.y(), p2.y());
    }
    friend bool operator!=(const PointF& p1, const PointF& p2)
    {
        return !fuzzyCompare(p1.x(), p2.x()) || !fuzzyCompare(p1.y(), p2.y());
    }
    friend const PointF operator+(const PointF& p1, const PointF& p2)
    {
        return PointF(p1.x() + p2.x(), p1.y() + p2.y());
    }
    friend const PointF operator-(const PointF& p1, const PointF& p2)
    {
        return PointF(p1.x() - p2.x(), p1.y() - p2.y());
    }
    template <class T, class S>
    friend const PointF operator/(const PointF& p1, T divisor);

    template <class T, class S>
    friend const PointF operator*(const PointF& p1, T factor);
    template <class T, class S>
    friend const PointF operator*(T factor, const PointF& p1);

private:
    real mX, mY;
};
template <class T,
    class S = std::enable_if<std::is_floating_point<T>::value>::type>
const PointF operator/(const PointF& p1, T divisor)
{
    return PointF(p1.x() / divisor, p1.x() / divisor);
}
template <class T = int, class S = int>
const PointF operator/(const PointF& p1, int divisor)
{
    assert(divisor != 0);
    return PointF(p1.x() / divisor, p1.y() / divisor);
}
template <class T, class S = std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
const PointF operator*(const PointF& p1, T factor)
{
    return PointF(p1.x() * factor, p1.y() * factor);
}

template <class T, class S = std::enable_if<std::is_floating_point<T>::value || std::is_integral<T>::value>::type>
const PointF operator*(T factor, const PointF& p1)
{
    return PointF(p1.x() * factor, p1.y() * factor);
}

} // namespace TaoMath
