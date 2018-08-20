#pragma once
#include "Global.h"
#include "Common.hpp"
namespace TaoMath {
class Vector4D {
public:
    constexpr inline Vector4D () : mX (0), mY (0), mZ (0), mW(0) {}
    constexpr inline Vector4D (real x, real y, real z, real w) : mX (x), mY (y), mZ (z), mW(w) {}
    constexpr inline real x () const { return mX; }
    constexpr inline real y () const { return mY; }
    constexpr inline real z () const { return mZ; }
    constexpr inline real w () const { return mW; }
    constexpr inline void setX (real x) { mX = x; }
    constexpr inline void setY (real y) { mY = y; }
    constexpr inline void setZ (real z) { mZ = z; }
    constexpr inline void setW (real w) { mW = w; }

    friend inline bool operator==(const Vector4D& v1, const Vector4D& v2);
private:
    real mX, mY, mZ, mW;
};
inline bool operator==(const Vector4D& v1, const Vector4D& v2) {
    return fuzzyCompare (v1.x (), v2.x ()) && fuzzyCompare (v1.y (), v2.y ()) && fuzzyCompare (v1.z (), v2.z ()) && fuzzyCompare (v1.w (), v2.w ());
}
}