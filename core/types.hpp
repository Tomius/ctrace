#ifndef CORE_TYPES_HPP_
#define CORE_TYPES_HPP_

#include "../math/vec3.hpp"
#include "../scene_settings.hpp"

namespace ctrace {

struct Ray {
  Vector origin, direction;
  constexpr Ray(Vector const& origin, Vector const& direction)
    : origin(origin), direction(direction) {}
};

struct Fragment {
  // if negative, the intersection is considered invalid.
  real distance_from_eye = -1;
  Color color = kBackgroundColor;
  constexpr Fragment() {}
  constexpr Fragment(real distance_from_eye, Color const& color)
      : distance_from_eye(distance_from_eye), color(color) {}
};

}

#endif
