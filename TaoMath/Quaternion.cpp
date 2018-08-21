#include "Quaternion.hpp"
#include "Vector3D.hpp"
#include "Vector4D.hpp"
namespace TaoMath {
inline constexpr Quaternion::Quaternion(real scalar, const Vector3D& v)
    : mScalar(scalar)
    , mX(v.x())
    , mY(v.y())
    , mZ(v.z())
{
}
inline constexpr Quaternion::Quaternion(const Vector4D& v)
    : mScalar(v.w())
    , mX(v.x())
    , mY(v.y())
    , mZ(v.z())
{
}
Vector3D Quaternion::vector() const
{
    return Vector3D(mX, mY, mZ);
}
void Quaternion::setVector(const Vector3D& vector)
{
    mX = vector.x();
    mY = vector.y();
    mZ = vector.z();
}
void Quaternion::setVector(real x, real y, real z)
{
    mX = x;
    mY = y;
    mZ = z;
}
Vector4D Quaternion::toVector4D() const
{
    return Vector4D(mX, mY, mZ, mScalar);
}
void Quaternion::getAxisAndAngle(Vector3D& axis, real& angle) const
{
    real x, y, z;
    getAxisAndAngle(x, y, z, angle);
    axis = Vector3D(x, y, z);
}
void Quaternion::getAxisAndAngle(real& x, real& y, real& z, real& angle) const
{
    auto len = lengthSquared();
    if (!isZero(len)) {
        x = mX;
        y = mY;
        z = mZ;
        if (!isZero(len - 1.0f)) {
            len = std::sqrt(len);
            x /= len;
            y /= len;
            z /= len;
        }
        angle = 2.0f * std::acos(mScalar);
    } else {
        x = y = z = angle = 0.0f;
    }
    angle = radiansToDegrees(angle);
}
Vector3D Quaternion::toEulerAngles() const
{
    real pitch, yaw, roll;
    getEulerAngles(pitch, yaw, roll);
    return Vector3D(pitch, yaw, roll);
}
void Quaternion::getEulerAngles(real& pitch, real& yaw, real& roll) const
{
    real xx = mX * mX;
    real xy = mX * mY;
    real xz = mX * mZ;
    real xw = mX * mScalar;
    real yy = mY * mY;
    real yz = mY * mZ;
    real yw = mY * mScalar;
    real zz = mZ * mZ;
    real zw = mZ * mScalar;

    const real lengthSquared = xx + yy + zz + mScalar * mScalar;
    if (!isZero(lengthSquared - 1.0f) && !isZero(lengthSquared)) {
        xx /= lengthSquared;
        xy /= lengthSquared;
        xz /= lengthSquared;
        xw /= lengthSquared;
        yy /= lengthSquared;
        yz /= lengthSquared;
        yw /= lengthSquared;
        zz /= lengthSquared;
        zw /= lengthSquared;
    }
    pitch = std::asin(-2.0f * (yz - xw));
    if (pitch < PI_2) {
        if (pitch > -PI_2) {
            yaw = std::atan2(2.0f * (xz + yw), 1.0f - 2.0f * (xx + yy));
            roll = std::atan2(2.0f * (xy + zw), 1.0f - 2.0f * (xx + zz));
        } else {
            roll = 0.0f;
            yaw = -std::atan2(-2.0f * (xy - zw), 1.0 - 2.0f * (yy + zz));
        }
    } else {
        roll = 0.0f;
        yaw = std::atan2(-2.0f * (xy - zw), 1.0f - 2.0f * (yy + zz));
    }
    pitch = radiansToDegrees(pitch);
    yaw = radiansToDegrees(yaw);
    roll = radiansToDegrees(roll);
}

bool Quaternion::isNull() const
{
    return mScalar == 0.0f && mX == 0.0f && mY == 0.0f && mZ == 0.0f;
}
bool Quaternion::isIdentity() const
{
    return mScalar == 1.0f && mX == 0.0f && mY == 0.0f && mZ == 0.0f;
}
real Quaternion::length() const
{
    return std::sqrt(lengthSquared());
}
real Quaternion::lengthSquared() const
{
    return mScalar * mScalar + mX * mX + mY * mY + mZ * mZ;
}
Quaternion Quaternion::normalized() const
{
    double len = lengthSquared();
    if (isZero(len)) {
        return {};
    } else if (isZero(len - 1.0f)) {
        return *this;
    } else {
        len = std::sqrt(len);
        return { mScalar / len, mX / len, mY / len, mZ / len };
    }
}
void Quaternion::normalize()
{
    double len = lengthSquared();
    if (isZero(len) || isZero(len - 1.0f)) {
        return;
    } else {
        len = std::sqrt(len);
        mX /= len;
        mY /= len;
        mZ /= len;
        mScalar /= len;
    }
}
inline const Quaternion Quaternion::inverted() const
{
    auto len = lengthSquared();
    if (!isZero(len)) {
        return Quaternion(mScalar / len, mX / len, mY / len, mZ / len);
    }
    return Quaternion();
}
inline constexpr const Quaternion Quaternion::conjugated() const
{
    return Quaternion(mScalar, -mX, -mY, -mZ);
}
Vector3D Quaternion::rotatedVector(const Vector3D& v) const
{
    return (*this * Quaternion(0., v) * conjugated()).vector();
}
Quaternion Quaternion::fromAxisAndAngle(real x, real y, real z, real angle)
{
    auto len = std::sqrt(x * x + y * y + z * z);
    if (!isZero(len - 1.0f) && !isZero(len)) {
        x /= len;
        y /= len;
        z /= len;
    }
    real a = degreesToRadians(angle / 2.0f);
    real s = std::sin(a);
    real c = std::cos(a);
    return Quaternion(c, x * s, y * s, z * s).normalized();
}
Quaternion Quaternion::fromAxisAndAngle(const Vector3D& axis, real angle)
{
    auto v = axis.normalized();
    real a = degreesToRadians(angle / 2.0f);
    real s = std::sin(a);
    real c = std::cos(a);
    return Quaternion(c, v.x() * s, v.y() * s, v.z() * s).normalized();
}
Quaternion Quaternion::fromEulerAngles(real pitch, real yaw, real roll)
{
    pitch = degreesToRadians(pitch) * 0.5f;
    yaw = degreesToRadians(yaw) * 0.5f;
    roll = degreesToRadians(roll) * 0.5f;
    real c1 = std::cos(yaw);
    real s1 = std::sin(yaw);
    real c2 = std::cos(roll);
    real s2 = std::sin(roll);
    real c3 = std::cos(pitch);
    real s3 = std::sin(pitch);
    real c1c2 = c1 * c2;
    real s1s2 = s1 * s2;
    real w = c1c2 * c3 + s1s2 * s3;
    real x = c1c2 * s3 + s1s2 * c3;
    real y = s1 * c2 * c3 - c1 * s2 * s3;
    real z = c1 * s2 * c3 - s1 * c2 * s3;
    return Quaternion(w, x, y, z);
}
Quaternion Quaternion::fromEulerAngles(const Vector3D& eulerAngles)
{
    return fromEulerAngles(eulerAngles.x(), eulerAngles.y(), eulerAngles.z());
}
Quaternion Quaternion::fromAxes(const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis)
{
    return Quaternion();
}
void Quaternion::getAxes(Vector3D& xAxis, Vector3D& yAxis, Vector3D& zAxis) const
{
}
Quaternion Quaternion::fromDirection(const Vector3D& direction, const Vector3D& up)
{
    if (direction.isNull()) {
        return {};
    }
    auto z = direction.normalized();
    auto x = Vector3D::crossProduct(up, z);
    if (isZero(x.lengthSquared())) {
        return Quaternion::rotationTo(Vector3D(0.0f, 0.0f, 1.0f), z);
    }
    x.normalize();
    auto y = Vector3D::crossProduct(z, x);
    return Quaternion::fromAxes(x, y, z);
}
Quaternion Quaternion::rotationTo(const Vector3D& from, const Vector3D& to)
{
    auto v0 = from.normalized();
    auto v1 = to.normalized();

    real d = Vector3D::dotProduct(v0, v1) + 1.0f;

    if (isZero(d)) {
        auto axis = Vector3D::crossProduct(Vector3D(1.0f, 0.0f, 0.0f), v0);
        if (isZero(axis.lengthSquared())) {
            axis = Vector3D::crossProduct(Vector3D(0.0f, 1.0f, 0.0f), v0);
        }
        axis.normalize();
        return { 0.0f, axis.x(), axis.y(), axis.z() };
    }
    d = std::sqrt(2.0f * d);
    auto axis = Vector3D::crossProduct(v0, v1) / d;
    return Quaternion(d * 0.5f, axis).normalized();
}
Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, real t)
{
    if (t <= 0.0f) {
        return q1;
    } else if (t >= 1.0f) {
        return q2;
    }
    Quaternion q2b(q2);
    real dot = Quaternion::dotProduct(q1, q2);
    if (dot < 0.0f) {
        q2b = -q2b;
        dot = -dot;
    }

    real factor1 = 1.0f - t;
    real factor2 = t;
    if (!isZero(dot - 1.0f)) {
        real angle = std::acos(dot);
        real sinOfAngle = std::sin(angle);
        if (sinOfAngle > 0.0000001) {
            factor1 = std::sin((1.0f - t) * angle) / sinOfAngle;
            factor2 = std::sin(t * angle) / sinOfAngle;
        }
    }

    return q1 * factor1 + q2 * factor2;
}
Quaternion Quaternion::nlerp(const Quaternion& q1, const Quaternion& q2, real t)
{
    if (t <= 0.0f) {
        return q1;
    } else if (t >= 1.0f) {
        return q2;
    }
    Quaternion q2b(q2);
    real dot = Quaternion::dotProduct(q1, q2);
    if (dot < 0.0f) {
        q2b = -q2b;
    }
    return (q1 * (1.0f - t) + q2b * t).normalized();
}
real Quaternion::dotProduct(const Quaternion& q1, const Quaternion& q2)
{
    return q1.mScalar * q2.mScalar + q1.mX * q2.mX + q1.mY * q2.mY + q1.mZ * q2.mZ;
}
inline constexpr Quaternion& Quaternion::operator+=(const Quaternion& q)
{
    mX += q.mX;
    mY += q.mY;
    mZ += q.mZ;
    mScalar += q.mScalar;
    return *this;
}
inline constexpr Quaternion& Quaternion::operator-=(const Quaternion& q)
{
    mX -= q.mX;
    mY -= q.mY;
    mZ -= q.mZ;
    mScalar -= q.mScalar;
    return *this;
}
inline constexpr Quaternion& Quaternion::operator*=(const Quaternion& q)
{
    mX *= q.mX;
    mY *= q.mY;
    mZ *= q.mZ;
    mScalar *= q.mScalar;
    return *this;
}
} // TaoMath
