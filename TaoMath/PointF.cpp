#include "PointF.hpp"
#include "Point.hpp"

namespace TaoMath {

constexpr inline Point PointF::toPoint () const {
    return Point (static_cast<Integer>(mX), static_cast<Integer>(mY));
}

}