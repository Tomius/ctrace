#ifndef MATH_VEC3_HPP_
#define MATH_VEC3_HPP_

#include <cmath>
#include <cstdint>
#include "./const_math.hpp"

namespace ctrace {

struct vec3 {
  union { float x, r; }; // we want to reference this field with either .x or .r
  union { float y, g; };
  union { float z, b; };

  // ctors
  constexpr vec3(float v=0) : x(v), y(v), z(v) {}
  constexpr vec3(float x, float y, float z) : x(x), y(y), z(z) {}
  constexpr vec3(vec3 const& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

  // +-*/
  constexpr vec3 operator+(vec3 const& v) const {
    return vec3{x + v.x, y + v.y, z + v.z};
  }
  constexpr vec3 operator-(vec3 const& v) const {
    return vec3{x - v.x, y - v.y, z - v.z};
  }
  constexpr vec3 operator*(vec3 const& v) const {
    return vec3{x * v.x, y * v.y, z * v.z};
  }
  constexpr vec3 operator/(vec3 const& v) const {
    return vec3{x / v.x, y / v.y, z / v.z};
  }

  friend constexpr vec3 operator+(float f, const vec3& v) { return v+f; }
  friend constexpr vec3 operator-(float f, const vec3& v) { return vec3{f}-v; }
  friend constexpr vec3 operator*(float f, const vec3& v) { return v*f; }
  friend constexpr vec3 operator/(float f, const vec3& v) { return vec3{f}/v; }

  friend constexpr float dot(const vec3& lhs, const vec3& rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
  }

  friend constexpr vec3 cross(const vec3& lhs, const vec3& rhs) {
    return vec3{lhs.y*rhs.z - lhs.z*rhs.y,
                lhs.z*rhs.x - lhs.x*rhs.z,
                lhs.x*rhs.y - lhs.y*rhs.x};
  }

  friend constexpr float length(const vec3& v) {
    return sqrt(dot(v, v));
  }

  friend constexpr vec3 normalize(const vec3& v) {
    float l = length(v);
    if(l > 1e-3) {
      return (v/l);
    } else {
      return vec3();
    }
  }

  friend constexpr bool isNull(const vec3& v) {
    return length(v) < 1e-3;
  }
};

}


#endif
