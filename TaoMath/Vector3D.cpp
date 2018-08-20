#include "Vector3D.hpp"
#include "TaoMath"
namespace TaoMath {
inline constexpr Vector3D::Vector3D (const Vector2D & o) : mX(o.x()), mY (o.y()), mZ(0){}
inline constexpr Vector3D::Vector3D (const Vector4D & o) : mX (o.x()), mY (o.y ()), mZ (o.z()) {}
inline constexpr Vector3D::Vector3D (const Point & o) : mX (o.x()), mY (o.y ()), mZ (0) {}
inline constexpr Vector3D::Vector3D (const PointF & o) : mX (o.x()), mY (o.y ()), mZ (0) {}
inline constexpr Point Vector3D::toPoint () const {
    return Point (static_cast<Integer>(mX), static_cast<Integer>(mY));
}
inline constexpr PointF Vector3D::toPointF () const {
    return PointF (mX, mY);
}
inline constexpr Vector2D Vector3D::toVector2D () const {
    return Vector2D (mX, mY);
}
inline constexpr Vector4D Vector3D::toVector4D () const {
    return Vector4D (mX, mY, mZ, 0.0);
}
real Vector3D::length () const {
    return real ();
}
real Vector3D::lengthSquared () const {
    return real ();
}
inline constexpr void Vector3D::normalize () {}
inline constexpr Vector3D Vector3D::normalized () const {
    return Vector3D ();
}
real Vector3D::distanceToPoint (const Vector3D & point) const {
    return real ();
}
real Vector3D::distanceToPlane (const Vector3D & plane, const Vector3D & normal) const {
    return real ();
}
real Vector3D::distanceToPlane (const Vector3D & plane1, const Vector3D & plane2, const Vector3D & plane3) const {
    return real ();
}
real Vector3D::distanceToLine (const Vector3D & point, const Vector3D & direction) const {
    return real ();
}
real Vector3D::dotProduct (const Vector3D & v1, const Vector3D & v2) {
    return real ();
}
Vector3D Vector3D::crossProduct (const Vector3D & v1, const Vector3D & v2) {
    return Vector3D ();
}
Vector3D Vector3D::normal (const Vector3D & v1, const Vector3D & v2) {
    return Vector3D ();
}
Vector3D Vector3D::normal (const Vector3D & v1, const Vector3D & v2, const Vector3D & v3) {
    return Vector3D ();
}

}