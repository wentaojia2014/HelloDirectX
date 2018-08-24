#include "Vector4D.hpp"
#include "Point.hpp"
#include "PointF.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"
namespace TaoMath {
Vector4D::Vector4D(const Vector2D& o)
    : mX(o.x())
    , mY(o.y())
    , mZ(0)
    , mW(0)
{
}
Vector4D::Vector4D(const Vector3D& o)
    : mX(o.x())
    , mY(o.y())
    , mZ(o.z())
    , mW(0)
{
}
Vector4D::Vector4D(const Point& o)
    : mX(o.x())
    , mY(o.y())
    , mZ(0)
    , mW(0)
{
}
Vector4D::Vector4D(const PointF& o)
    : mX(o.x())
    , mY(o.y())
    , mZ(0)
    , mW(0)
{
}
Point Vector4D::toPoint() const
{
    return Point(static_cast<Integer>(mX), static_cast<Integer>(mY));
}
PointF Vector4D::toPointF() const
{
    return PointF(mX, mY);
}
Vector2D Vector4D::toVector2D() const
{
    return Vector2D(mX, mY);
}
Vector3D Vector4D::toVector3D() const
{
    return Vector3D(mX, mY, mZ);
}
bool Vector4D::isNull() const
{
    return isZero (mX) && isZero (mY) && isZero (mZ) && isZero (mW);
}
real Vector4D::length() const
{
    return std::sqrt (lengthSquared ());
}
real Vector4D::lengthSquared() const
{
    return mX * mX + mY * mY + mZ * mZ + mW * mW;
}
Vector4D Vector4D::normalized() const
{
    auto len = lengthSquared ();
    if (isZero (len)) {
        return {};
    } else if (isZero (len - 1)) {
        return *this;
    } else {
        len = std::sqrt (len);
        return { mX / len, mY / len, mZ / len, mW / len };
    }
}
void Vector4D::normalize() {
    auto len = lengthSquared ();
    if (isZero (len) || isZero (len - 1)) {
        return;
    } else {
        len = std::sqrt (len);
        mX /= len;
        mY /= len;
        mZ /= len;
        mW /= len;
    }
}
real Vector4D::dotProduct(const Vector4D& v1, const Vector4D& v2)
{
    return v1.x () * v2.x () + v1.y () * v2.y () + v1.z () * v2.z () + v1.w() * v2.w();
}
}
