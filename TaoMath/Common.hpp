#pragma once
#include "Global.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <type_traits>
#include <utility>
namespace TaoMath {

using Integer = int;
using real = double;
enum class State {
    Uninitialized
};
static const auto PI = (3.14159265358979323846);
static const auto PI_2 = 1.57079632679489661923;
template <class T, class S = std::enable_if<std::is_floating_point<T>::value>::type>
inline static bool isZero(T v)
{
    return std::abs(v) < std::numeric_limits<T>::epsilon();
}

inline static bool fuzzyCompare(float p1, float p2)
{
    return std::abs(p1 - p2) * 100000.0f <= std::min(std::abs(p1), std::abs(p2));
}
inline static bool fuzzyCompare(double p1, double p2)
{
    return std::abs(p1 - p2) * 1000000000000. <= std::min(std::abs(p1), std::abs(p2));
}

constexpr inline static float radiansToDegrees(float radians)
{
    return radians * float(180 / PI);
}

constexpr inline static double radiansToDegrees(double radians)
{
    return radians * (180 / PI);
}

constexpr inline static float degreesToRadians(float degrees)
{
    return degrees * float(PI / 180);
}
constexpr inline static double degreesToRadians(double degrees)
{
    return degrees * (PI / 180);
}
}
