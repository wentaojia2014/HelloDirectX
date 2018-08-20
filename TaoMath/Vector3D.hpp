#pragma once
#include "Global.h"
#include "Common.hpp"
namespace TaoMath {

class TAOEXPORT Vector3D {
public:
    constexpr inline Vector3D () : mX (0), mY (0), mZ (0) {}
    constexpr inline Vector3D (real x, real y, real z) : mX (x), mY (y), mZ (z) {}
    constexpr inline real x () const { return mX; }
    constexpr inline real y () const { return mY; }
    constexpr inline real z () const { return mZ; }

    constexpr inline void setX (real x) { mX = x; }
    constexpr inline void setY (real y) { mY = y; }
    constexpr inline void setZ (real z) { mZ = z; }

private:
    real mX, mY, mZ;
};
} // TaoMath
