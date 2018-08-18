#pragma once
#include "Point.hpp"
#include "PointF.hpp"
namespace TaoMath {

class Vector2D {
public:
    Vector2D () : mX (0), mY (0) { }
    Vector2D (real x, real y) : mX (x), mY (y) { }
    Vector2D (const Point &o) : mX (o.x ()), mY (o.y ()) { }
    Vector2D (const PointF &o) : mX (o.x ()), mY (o.y ()) { }
    Vector2D (const Vector2D &o) : mX (o.mX), mY (o.mY) { }
    //Vector2D (const Vector3D &o) : mX (o.x ()), mY (o.y ()) { }
    //Vector2D (const Vector4D &o) : mX (o.x ()), mY (o.y ()) { }

    real x () const { return mX; }
    real y () const { return mY; }
    void setX (real x) { mX = x; }
    void setY (real y) { mY = y; }

    real distanceToLine (const Vector2D &point, const Vector2D &direction) const;
    real distanceToLine(const Vector2D& point) const;
    bool isNull () const;
    real length () const;
    real lengthSquared () const;
    void normalize ();
    Vector2D normalized () const;

    Point toPoint () const;
    PointF toPointF () const;
    //Vector3D toVector3D () const;
    //Vector4D toVector4D () const;
    Vector2D & operator*= (real factor);
    Vector2D & operator*= (const Vector2D &o);
    Vector2D & operator+= (const Vector2D &o);
    Vector2D & operator-= (const Vector2D &o);
    Vector2D & operator/= (const Vector2D &o);
    Vector2D & operator/= (real factor);

    static real dotProduct (const Vector2D &v1, const Vector2D &v2);

private:
    real mX, mY;
};
bool fuzzyCompare (const Vector2D &v1, const Vector2D &v2);
} // TaoMath
