#pragma once
#include "Global.h"
#include "Common.hpp"
namespace TaoMath {
class Vector4D {
public:
    constexpr inline real x () const { return mX; }
    constexpr inline real y () const { return mY; }
    constexpr inline real z () const { return mZ; }
    constexpr inline real W () const { return mW; }
    constexpr inline void setX (real x) { mX = x; }
    constexpr inline void setY (real y) { mY = y; }
    constexpr inline void setZ (real z) { mZ = z; }
    constexpr inline void setW (real w) { mW = w; }
private:
    real mX, mY, mZ, mW;
};
}