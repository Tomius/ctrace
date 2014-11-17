#ifndef CORE_TYPES_HPP_
#define CORE_TYPES_HPP_

#include "../math/vec3.hpp"

namespace ctrace {

struct Ray {
  vec3 origin, direction;
  constexpr Ray(vec3 const& origin, vec3 const& direction)
    : origin(origin), direction(direction) {}
};

struct Fragment {
  // if negative, the intersection is considered invalid.
  float distance_from_eye = -1;
  vec3 color;
  constexpr Fragment() {}
  constexpr Fragment(float distance_from_eye, vec3 const& color)
      : distance_from_eye(distance_from_eye), color(color) {}
};

}

#endif
