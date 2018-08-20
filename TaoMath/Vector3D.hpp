#pragma once
#include "Global.h"
#include "Common.hpp"
namespace TaoMath {

class TAOAPI Vector3D {
public:
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
