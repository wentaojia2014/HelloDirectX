#pragma once
#include "Global.h"
#include "Common.hpp"

namespace TaoMath {
class Point;
class PointF;
class Vector3D;
class Vector4D;
class TAOAPI Vector2D {
public:
    constexpr inline Vector2D () : mX (0), mY (0) { }
    constexpr inline Vector2D (real x, real y) : mX (x), mY (y) { }
    constexpr inline Vector2D (const Vector2D &o) : mX (o.mX), mY (o.mY) { }

    constexpr inline Vector2D (const Point &o);
    constexpr inline Vector2D (const PointF &o);
    constexpr inline Vector2D (const Vector3D &o);
    constexpr inline Vector2D (const Vector4D &o);

    constexpr inline real x () const { return mX; }
    constexpr inline real y () const { return mY; }
    constexpr inline void setX (real x) { mX = x; }
    constexpr inline void setY (real y) { mY = y; }

    real distanceToLine (const Vector2D &point, const Vector2D &direction) const;
    real distanceToPoint (const Vector2D& point) const;
    inline bool isNull () const;
    inline real length () const;
    inline real lengthSquared () const;
    constexpr inline void normalize ();
    constexpr inline Vector2D normalized () const;

    constexpr inline Point toPoint () const;
    constexpr inline PointF toPointF () const;
    constexpr inline Vector3D toVector3D () const;
    constexpr inline Vector4D toVector4D () const;

    Vector2D & operator+= (const Vector2D &o);
    Vector2D & operator-= (const Vector2D &o);
    Vector2D & operator*= (real factor);
    Vector2D & operator*= (const Vector2D &o);
    Vector2D & operator/= (const Vector2D &o);
    Vector2D & operator/= (real factor);

    static real dotProduct (const Vector2D &v1, const Vector2D &v2);

    friend inline bool operator== (const Vector2D &v1, const Vector2D &v2);
    friend inline bool operator!= (const Vector2D &v1, const Vector2D &v2);
    friend inline bool fuzzyCompare (const Vector2D &v1, const Vector2D &v2);
    friend constexpr inline const Vector2D operator+ (const Vector2D &v1, const Vector2D &v2);
    friend constexpr inline const Vector2D operator- (const Vector2D &v1, const Vector2D &v2);
    friend constexpr inline const Vector2D operator* (const Vector2D &v1, const Vector2D &v2);
    friend constexpr inline const Vector2D operator* (const Vector2D &v, real factor);
    friend constexpr inline const Vector2D operator* (real factor, const Vector2D &v1);
    friend constexpr inline const Vector2D operator/ (const Vector2D &v1, const Vector2D &v2);
    friend constexpr inline const Vector2D operator/ (const Vector2D &v1, real divisor);
private:
    real mX, mY;
};
} // TaoMath
