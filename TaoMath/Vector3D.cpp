#include "Vector3D.hpp"
#include "Point.hpp"
#include "PointF.hpp"
#include "Vector2D.hpp"
#include "Vector4D.hpp"
namespace TaoMath
{
Vector3D::Vector3D(const Vector2D &o) : mX(o.x()), mY(o.y()), mZ(0) {}
Vector3D::Vector3D(const Vector4D &o) : mX(o.x()), mY(o.y()), mZ(o.z()) {}
Vector3D::Vector3D(const Point &o) : mX(o.x()), mY(o.y()), mZ(0) {}
Vector3D::Vector3D(const PointF &o) : mX(o.x()), mY(o.y()), mZ(0) {}
Point Vector3D::toPoint() const
{
    return Point(static_cast<Integer>(mX), static_cast<Integer>(mY));
}
PointF Vector3D::toPointF() const
{
    return PointF(mX, mY);
}
Vector2D Vector3D::toVector2D() const
{
    return Vector2D(mX, mY);
}
Vector4D Vector3D::toVector4D() const
{
    return Vector4D(mX, mY, mZ, 0);
}
bool Vector3D::isNull() const
{
    return isZero(mX) && isZero(mY) && isZero(mZ);
}
real Vector3D::length() const
{
    return std::sqrt(mX * mX + mY * mY + mZ * mZ);
}
real Vector3D::lengthSquared() const
{
    return mX * mX + mY * mY + mZ * mZ;
}
void Vector3D::normalize()
{
    auto len = lengthSquared();
    if (isZero(len) || isZero(len - 1))
    {
        return;
    }
    else
    {
        len = std::sqrt(len);
        mX /= len;
        mY /= len;
        mZ /= len;
    }
}
Vector3D Vector3D::normalized() const
{
    auto len = lengthSquared();
    if (isZero(len))
    {
        return {};
    }
    else if (isZero(len - 1))
    {
        return *this;
    }
    else
    {
        len = std::sqrt(len);
        return { mX / len, mY / len, mZ / len };
    }
}
real Vector3D::distanceToPoint(const Vector3D &point) const
{
    return (*this - point).length();
}
real Vector3D::distanceToPlane(
    const Vector3D &plane, const Vector3D &normal) const
{
    return dotProduct((*this - plane), normal);
}
real Vector3D::distanceToPlane(
    const Vector3D &plane1,
    const Vector3D &plane2,
    const Vector3D &plane3) const
{
    auto n = normal(plane2 - plane1, plane3 - plane1);
    return dotProduct(*this - plane1, n);
}
real Vector3D::distanceToLine(
    const Vector3D &point, const Vector3D &direction) const
{
    if (direction.isNull())
    {
        return (*this - point).length();
    }
    auto p = point + dotProduct(*this - point, direction) * direction;
    return (*this - p).length();
}
real Vector3D::dotProduct(const Vector3D &v1, const Vector3D &v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}
Vector3D Vector3D::crossProduct(const Vector3D &v1, const Vector3D &v2)
{
    return { v1.y() * v2.z() - v1.z() * v2.y(),
             v1.z() * v2.x() - v1.x() * v2.z(),
             v1.x() * v2.y() - v1.y() * v2.x() };
}
Vector3D Vector3D::normal(const Vector3D &v1, const Vector3D &v2)
{
    return crossProduct(v1, v2).normalized();
}
Vector3D
Vector3D::normal(const Vector3D &v1, const Vector3D &v2, const Vector3D &v3)
{
    return crossProduct((v2 - v1), (v3 - v1)).normalized();
}

} // namespace TaoMath
