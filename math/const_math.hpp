#ifndef MATH_CONST_MATH_HPP_
#define MATH_CONST_MATH_HPP_

#include <cmath>

#ifndef M_PI
  #define M_PI 3.141592653589793
#endif
#ifndef M_PI_2
  #define M_PI_2 1.570796326794897
#endif

namespace ctrace {

using real = float;

constexpr real kEpsilon = 0.001;

constexpr real abs(real x) { return x < 0.0 ? -x : x; }

constexpr real min(real a, real b) { return a < b ? a : b; }

constexpr real max(real a, real b) { return a < b ? b : a; }

constexpr real square(real x) { return x*x; }

constexpr real sqrt_helper(real x, real g) {
  return abs(g - x/g) < kEpsilon ? g : sqrt_helper(x, (g + x/g) / 2.0);
}

constexpr real sqrt(real x) { return sqrt_helper(x, 1.0); }

constexpr real cube(real x) { return x*x*x; }

// Based on the triple-angle formula: sin 3x = 3 sin x - 4 sin ^3 x
constexpr real sin_helper(real x) {
  return x < kEpsilon ? x : 3*(sin_helper(x/3)) - 4*cube(sin_helper(x/3));
}

constexpr real sin(real x) {
  return sin_helper(x < 0 ? -x+M_PI : x);
}

constexpr real cos(real x) { return sin(M_PI_2 - x); }

constexpr real tan(real x) { return sin(x) / cos(x); }

}

#endif // _CONST_MATH_HPP_
