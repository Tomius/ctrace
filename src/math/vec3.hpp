#ifndef MATH_VEC3_HPP_
#define MATH_VEC3_HPP_

#include "./const_math.hpp"

namespace ctrace {

// GLSL like vec3
struct vec3 {
  // we want to reference the first field
  // of a vec3 with either .x, .r or .s
  union { real x, r, s; };
  union { real y, g, t; };
  union { real z, b, p; };

  // ctors
  constexpr vec3(real v=0) : x(v), y(v), z(v) {}
  constexpr vec3(real x, real y, real z) : x(x), y(y), z(z) {}
  constexpr vec3(vec3 const& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
};

using Vector = vec3;
using Position = Vector;
using Direction = Vector;
using Color = vec3;

constexpr vec3 operator+(vec3 const& lhs, vec3 const& rhs) {
  return vec3{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

constexpr vec3 operator-(vec3 const& lhs, vec3 const& rhs) {
  return vec3{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

constexpr vec3 operator*(vec3 const& lhs, vec3 const& rhs) {
  return vec3{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

constexpr vec3 operator/(vec3 const& lhs, vec3 const& rhs) {
  return vec3{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

constexpr vec3 operator+(real f, vec3 const& v) { return v+f; }
constexpr vec3 operator-(real f, vec3 const& v) { return vec3{f}-v; }
constexpr vec3 operator*(real f, vec3 const& v) { return v*f; }
constexpr vec3 operator/(real f, vec3 const& v) { return vec3{f}/v; }

constexpr real dot(Vector const& lhs, Vector const& rhs) {
  return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

constexpr Vector cross(Vector const& lhs, Vector const& rhs) {
  return Vector{lhs.y*rhs.z - lhs.z*rhs.y,
                lhs.z*rhs.x - lhs.x*rhs.z,
                lhs.x*rhs.y - lhs.y*rhs.x};
}

constexpr real length(Vector const& v) {
  return sqrt(dot(v, v));
}

constexpr Vector normalize(Vector const& v) {
  real l = length(v);
  if(l > kEpsilon) {
    return (v/l);
  } else {
    return Vector();
  }
}

constexpr bool isNull(Vector const& v) {
  return length(v) < kEpsilon;
}

constexpr vec3 min(Vector const& lhs, Vector const& rhs) {
  return vec3{min(lhs.x, rhs.x), min(lhs.y, rhs.y), min(lhs.z, rhs.z)};
}

constexpr vec3 max(Vector const& lhs, Vector const& rhs) {
  return vec3{max(lhs.x, rhs.x), max(lhs.y, rhs.y), max(lhs.z, rhs.z)};
}

constexpr vec3 square(Vector const& v) {
  return vec3{square(v.x), square(v.y), square(v.z)};
}

constexpr Color toneMap(Color const& color) {
  Color x = max(0, color-0.004);
  Color srgb = (x*(6.2*x+0.5))/(x*(6.2*x+1.7)+0.06);
  return square(srgb); // approximation for the 2.2 exponent
}

}


#endif
