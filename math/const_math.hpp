#ifndef MATH_CONST_MATH_HPP_
#define MATH_CONST_MATH_HPP_

namespace ctrace {

#ifndef M_PI
#define M_PI   3.141592653589793
#endif

#ifndef M_PI_2
#define M_PI_2 1.570796326794897
#endif

#ifndef M_E
#define M_E    2.718281828459045
#endif

constexpr float kEpsilon = 0.001f;

constexpr float abs(float x) { return x < 0.0f ? -x : x; }

constexpr float min(float a, float b) { return a < b ? a : b; }

constexpr float max(float a, float b) { return a < b ? b : a; }

constexpr float square(float x) { return x*x; }

constexpr float sqrt_helper(float x, float g) {
  return abs(g - x/g) < kEpsilon ? g : sqrt_helper(x, (g + x/g) / 2.0f);
}

constexpr float sqrt(float x) { return sqrt_helper(x, 1.0f); }

constexpr float cube(float x) { return x*x*x; }

// Based on the triple-angle formula: sin 3x = 3 sin x - 4 sin ^3 x
constexpr float sin_helper(float x) {
  return x < kEpsilon ? x : 3*(sin_helper(x/3)) - 4*cube(sin_helper(x/3));
}

constexpr float sin(float x) {
  return sin_helper(x < 0 ? -x+M_PI : x);
}

constexpr float cos(float x) { return sin(M_PI_2 - x); }

constexpr float tan(float x) { return sin(x) / cos(x); }

}

#endif // _CONST_MATH_HPP_
