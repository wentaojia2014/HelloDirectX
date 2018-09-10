#include "PointF.hpp"
#include "Point.hpp"

namespace TaoMath
{

Point PointF::toPoint() const
{
    return Point(static_cast<Integer>(mX), static_cast<Integer>(mY));
}

} // namespace TaoMath
