#include "Quaternion.hpp"

namespace TaoMath {
Quaternion::Quaternion(real scalar, const Vector3D& v)
    : mX(v.x())
    , mY(v.y())
    , mZ(v.z())
    , mScalar(scalar)
{
}
Quaternion::Quaternion(const Vector4D& v)
    : mX(v.x())
    , mY(v.y())
    , mZ(v.z())
    , mScalar(v.w())
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
        if (!isZero(len - 1)) {
            len = std::sqrt(len);
            x /= len;
            y /= len;
            z /= len;
        }
        angle = 2 * std::acos(mScalar);
    } else {
        x = y = z = angle = 0;
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
    if (!isZero(lengthSquared - 1) && !isZero(lengthSquared)) {
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
    pitch = std::asin(-2 * (yz - xw));
    if (pitch < PI_2) {
        if (pitch > -PI_2) {
            yaw = std::atan2(2 * (xz + yw), 1 - 2 * (xx + yy));
            roll = std::atan2(2 * (xy + zw), 1 - 2 * (xx + zz));
        } else {
            roll = 0;
            yaw = -std::atan2(-2 * (xy - zw), 1 - 2 * (yy + zz));
        }
    } else {
        roll = 0.0;
        yaw = std::atan2(-2 * (xy - zw), 1 - 2 * (yy + zz));
    }
    pitch = radiansToDegrees(pitch);
    yaw = radiansToDegrees(yaw);
    roll = radiansToDegrees(roll);
}

Matrix3x3 Quaternion::toRotationMatrix () const {
    Matrix3x3 rot3x3 (State::Uninitialized);

    const float f2x = mX + mX;
    const float f2y = mY + mY;
    const float f2z = mZ + mZ;
    const float f2xw = f2x * mScalar;
    const float f2yw = f2y * mScalar;
    const float f2zw = f2z * mScalar;
    const float f2xx = f2x * mX;
    const float f2xy = f2x * mY;
    const float f2xz = f2x * mZ;
    const float f2yy = f2y * mY;
    const float f2yz = f2y * mZ;
    const float f2zz = f2z * mZ;

    rot3x3 (0, 0) = 1.0f - (f2yy + f2zz);
    rot3x3 (0, 1) = f2xy - f2zw;
    rot3x3 (0, 2) = f2xz + f2yw;
    rot3x3 (1, 0) = f2xy + f2zw;
    rot3x3 (1, 1) = 1.0f - (f2xx + f2zz);
    rot3x3 (1, 2) = f2yz - f2xw;
    rot3x3 (2, 0) = f2xz - f2yw;
    rot3x3 (2, 1) = f2yz + f2xw;
    rot3x3 (2, 2) = 1.0f - (f2xx + f2yy);

    return rot3x3;
}

Quaternion Quaternion::fromRotationMatrix (const Matrix3x3 & rot3x3) {
    float scalar;
    float axis[3];

    const float trace = rot3x3 (0, 0) + rot3x3 (1, 1) + rot3x3 (2, 2);
    if (trace > 0.00000001f) {
        const float s = 2.0f * std::sqrt (trace + 1.0f);
        scalar = 0.25f * s;
        axis[0] = (rot3x3 (2, 1) - rot3x3 (1, 2)) / s;
        axis[1] = (rot3x3 (0, 2) - rot3x3 (2, 0)) / s;
        axis[2] = (rot3x3 (1, 0) - rot3x3 (0, 1)) / s;
    } else {
        static int s_next[3] = { 1, 2, 0 };
        int i = 0;
        if (rot3x3 (1, 1) > rot3x3 (0, 0))
            i = 1;
        if (rot3x3 (2, 2) > rot3x3 (i, i))
            i = 2;
        int j = s_next[i];
        int k = s_next[j];

        const float s = 2.0f * std::sqrt (rot3x3 (i, i) - rot3x3 (j, j) - rot3x3 (k, k) + 1.0f);
        axis[i] = 0.25f * s;
        scalar = (rot3x3 (k, j) - rot3x3 (j, k)) / s;
        axis[j] = (rot3x3 (j, i) + rot3x3 (i, j)) / s;
        axis[k] = (rot3x3 (k, i) + rot3x3 (i, k)) / s;
    }

    return Quaternion (scalar, axis[0], axis[1], axis[2]);
}

bool Quaternion::isNull() const
{
    return mScalar == 0.0 && mX == 0.0 && mY == 0.0 && mZ == 0.0;
}
bool Quaternion::isIdentity() const
{
    return mScalar == 1.0 && mX == 0.0 && mY == 0.0 && mZ == 0.0;
}
void Quaternion::setToIdentity()
{
    mScalar = 1.0;
    mX = 0.0;
    mY = 0.0;
    mZ = 0.0;
}
real Quaternion::length() const
{
    return std::sqrt(lengthSquared());
}
constexpr real Quaternion::lengthSquared() const
{
    return mScalar * mScalar + mX * mX + mY * mY + mZ * mZ;
}
Quaternion Quaternion::normalized() const
{
    auto len = lengthSquared();
    if (isZero(len)) {
        return {};
    } else if (isZero(len - 1.0)) {
        return *this;
    } else {
        len = std::sqrt(len);
        return { mScalar / len, mX / len, mY / len, mZ / len };
    }
}
void Quaternion::normalize()
{
    auto len = lengthSquared();
    if (isZero(len) || isZero(len - 1.0)) {
        return;
    } else {
        len = std::sqrt(len);
        mX /= len;
        mY /= len;
        mZ /= len;
        mScalar /= len;
    }
}
Quaternion Quaternion::inverted() const
{
    auto len = lengthSquared();
    if (!isZero(len)) {
        return Quaternion(mScalar / len, mX / len, mY / len, mZ / len);
    }
    return Quaternion();
}
Quaternion Quaternion::conjugated() const
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
    if (!isZero(len - 1.0) && !isZero(len)) {
        x /= len;
        y /= len;
        z /= len;
    }
    real a = degreesToRadians(angle / 2.0);
    real s = std::sin(a);
    real c = std::cos(a);
    return Quaternion(c, x * s, y * s, z * s).normalized();
}
Quaternion Quaternion::fromAxisAndAngle(const Vector3D& axis, real angle)
{
    auto v = axis.normalized();
    real a = degreesToRadians(angle / 2.0);
    real s = std::sin(a);
    real c = std::cos(a);
    return Quaternion(c, v.x() * s, v.y() * s, v.z() * s).normalized();
}
Quaternion Quaternion::fromEulerAngles(real pitch, real yaw, real roll)
{
    pitch = degreesToRadians(pitch) * 0.5;
    yaw = degreesToRadians(yaw) * 0.5;
    roll = degreesToRadians(roll) * 0.5;
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
    Matrix3x3 m (State::Uninitialized);
    m (0, 0) = xAxis.x ();
    m (1, 0) = xAxis.y ();
    m (2, 0) = xAxis.z ();
    m (0, 1) = yAxis.x ();
    m (1, 1) = yAxis.y ();
    m (2, 1) = yAxis.z ();
    m (0, 2) = zAxis.x ();
    m (1, 2) = zAxis.y ();
    m (2, 2) = zAxis.z ();
    return Quaternion::fromRotationMatrix(m);
}
void Quaternion::getAxes(Vector3D& xAxis, Vector3D& yAxis, Vector3D& zAxis) const
{
    Matrix3x3 m (toRotationMatrix ());
    xAxis = Vector3D (m (0, 0), m (1, 0), m (2, 0));
    yAxis = Vector3D (m (0, 1), m (1, 1), m (2, 1));
    zAxis = Vector3D (m (0, 2), m (1, 2), m (2, 2));

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
Quaternion& Quaternion::operator+=(const Quaternion& q)
{
    mX += q.mX;
    mY += q.mY;
    mZ += q.mZ;
    mScalar += q.mScalar;
    return *this;
}
Quaternion& Quaternion::operator-=(const Quaternion& q)
{
    mX -= q.mX;
    mY -= q.mY;
    mZ -= q.mZ;
    mScalar -= q.mScalar;
    return *this;
}
Quaternion& Quaternion::operator*=(const Quaternion& q)
{
    mX *= q.mX;
    mY *= q.mY;
    mZ *= q.mZ;
    mScalar *= q.mScalar;
    return *this;
}
} // TaoMath
