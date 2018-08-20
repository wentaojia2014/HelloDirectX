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
}
