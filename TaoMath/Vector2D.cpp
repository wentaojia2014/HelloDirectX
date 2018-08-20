#include "Vector2D.hpp"
#include "Point.hpp"
#include "PointF.hpp"
#include "Vector3D.hpp"
#include "Vector4D.hpp"
namespace TaoMath {
constexpr inline Vector2D::Vector2D (const Point & o) : mX (o.x ()), mY (o.y ()) { }
constexpr inline Vector2D::Vector2D (const PointF & o) : mX (o.x ()), mY (o.y ()) { }
constexpr inline Vector2D::Vector2D (const Vector3D & o) : mX (o.x ()), mY (o.y ()) { }
constexpr inline Vector2D::Vector2D (const Vector4D & o) : mX (o.x ()), mY (o.y ()) { }
real Vector2D::distanceToLine (const Vector2D & point, const Vector2D & direction) const {
    if (direction.isNull ()) {
        return (*this - point).length ();
    }
    auto p = point + dotProduct (*this - point, direction) * direction;
    return (*this - p).length ();
}
real Vector2D::distanceToPoint (const Vector2D & point) const {
    return (*this - point).length ();
}
inline bool Vector2D::isNull () const {
    return isZero (mX) && isZero (mY);
}
inline real Vector2D::length () const {
    return static_cast<real>(std::sqrt (std::pow (x (), 2) + std::pow (y (), 2)));
}
inline real Vector2D::lengthSquared () const {
    return x () * x () + y () * y ();
}
inline constexpr void Vector2D::normalize () { 
    double len = lengthSquared ();
    if (isZero (len - 1.0) || isZero (len)) {
        return;
    }
    len = std::sqrt (len);
    mX = static_cast<real>(mX / len);
    mY = static_cast<real>(mY / len);

}
inline constexpr Vector2D Vector2D::normalized () const {
    double len = lengthSquared ();
    if (isZero (len - 1.0f)) {
        return *this;
    } else if (!isZero (len)) {
        len = sqrt (len);
        return Vector2D (static_cast<real>(mX / len), static_cast<real>(mY / len));
    } else {
        return Vector2D ();
    }

}
inline constexpr Point Vector2D::toPoint () const {
    return Point ();
}
inline constexpr PointF Vector2D::toPointF () const {
    return PointF ();
}
Vector3D Vector2D::toVector3D () const {
    return Vector3D ();
}
Vector4D Vector2D::toVector4D () const {
    return Vector4D ();
}
Vector2D & Vector2D::operator+=(const Vector2D & o) {
    // TODO: 在此处插入 return 语句
}
Vector2D & Vector2D::operator-=(const Vector2D & o) {
    // TODO: 在此处插入 return 语句
}
Vector2D & Vector2D::operator*=(real factor) {
    // TODO: 在此处插入 return 语句
}
Vector2D & Vector2D::operator*=(const Vector2D & o) {
    // TODO: 在此处插入 return 语句
}
Vector2D & Vector2D::operator/=(const Vector2D & o) {
    // TODO: 在此处插入 return 语句
}
Vector2D & Vector2D::operator/=(real factor) {
    // TODO: 在此处插入 return 语句
}
real Vector2D::dotProduct (const Vector2D & v1, const Vector2D & v2) {
    return v1.x () * v2.x () + v1.y () * v2.y ();
}
bool operator==(const Vector2D & v1, const Vector2D & v2) {
    return false;
}
bool operator!=(const Vector2D & v1, const Vector2D & v2) {
    return false;
}
bool fuzzyCompare (const Vector2D & v1, const Vector2D & v2) {
    return fuzzyCompare (v1.x (), v2.x ()) && fuzzyCompare (v1.y (), v2.y ());
}
constexpr const Vector2D operator+(const Vector2D & v1, const Vector2D & v2) {
    return Vector2D ();
}
constexpr const Vector2D operator-(const Vector2D & v1, const Vector2D & v2) {
    return Vector2D ();
}
constexpr const Vector2D operator*(const Vector2D & v1, const Vector2D & v2) {
    return Vector2D ();
}
constexpr const Vector2D operator*(const Vector2D & v, real factor) {
    return Vector2D ();
}
constexpr const Vector2D operator*(real factor, const Vector2D & v1) {
    return Vector2D ();
}
constexpr const Vector2D operator/(const Vector2D & v1, const Vector2D & v2) {
    return Vector2D ();
}
constexpr const Vector2D operator/(const Vector2D & v1, real divisor) {
    return Vector2D ();
}
}