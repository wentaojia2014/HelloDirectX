#include "Vector2D.hpp"
#include "Point.hpp"
#include "PointF.hpp"
#include "Vector3D.hpp"
#include "Vector4D.hpp"
namespace TaoMath {
constexpr inline Vector2D::Vector2D(const Point& o)
    : mX(o.x())
    , mY(o.y())
{
}
constexpr inline Vector2D::Vector2D(const PointF& o)
    : mX(o.x())
    , mY(o.y())
{
}
constexpr inline Vector2D::Vector2D(const Vector3D& o)
    : mX(o.x())
    , mY(o.y())
{
}
constexpr inline Vector2D::Vector2D(const Vector4D& o)
    : mX(o.x())
    , mY(o.y())
{
}
real Vector2D::distanceToLine(const Vector2D& point, const Vector2D& direction) const
{
    if (direction.isNull()) {
        return (*this - point).length();
    }
    auto dir = direction.normalized();
    auto p = point + dotProduct(*this - point, dir) * dir;
    return (*this - p).length();
}
real Vector2D::distanceToPoint(const Vector2D& point) const
{
    return (*this - point).length();
}
inline bool Vector2D::isNull() const
{
    return isZero(mX) && isZero(mY);
}
inline real Vector2D::length() const
{
    return static_cast<real>(std::sqrt(std::pow(x(), 2) + std::pow(y(), 2)));
}
inline real Vector2D::lengthSquared() const
{
    return x() * x() + y() * y();
}
inline void Vector2D::normalize()
{
    double len = lengthSquared();
    if (isZero(len - 1.0) || isZero(len)) {
        return;
    }
    len = std::sqrt(len);
    mX = static_cast<real>(mX / len);
    mY = static_cast<real>(mY / len);
}
inline Vector2D Vector2D::normalized() const
{
    double len = lengthSquared();
    if (isZero (len)) {
        return {};
    } else if (isZero(len - 1.0f)) {
        return *this;
    } else {
        len = sqrt(len);
        return Vector2D(static_cast<real>(mX / len), static_cast<real>(mY / len));
    }
}
inline constexpr Point Vector2D::toPoint() const
{
    return Point(static_cast<Integer>(x()), static_cast<Integer>(y()));
}
inline constexpr PointF Vector2D::toPointF() const
{
    return PointF(x(), y());
}
constexpr Vector3D Vector2D::toVector3D() const
{
    return Vector3D(x(), y(), 0);
}
constexpr Vector4D Vector2D::toVector4D() const
{
    return Vector4D(x(), y(), 0, 0);
}

}
