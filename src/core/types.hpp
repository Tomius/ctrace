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

struct Intersection {
  real dist_eye; // distance from eye
  Position pos;
  Direction normal;

  constexpr Intersection(real dist_eye, Position const& pos,
                         Direction const& normal)
      : dist_eye(dist_eye), pos(pos), normal(normal) {}
};

constexpr bool isValid(Intersection const& inter) {
  return inter.dist_eye >= 0;
}

constexpr bool isFirstCloser(Intersection const& a,
                             Intersection const& b) {
  return isValid(a) && (!isValid(b) || a.dist_eye < b.dist_eye);
}

constexpr Intersection closerOneOf(Intersection const& a,
                                   Intersection const& b) {
  return isFirstCloser(a, b) ? a : b;
}

struct NoIntersection : public Intersection {
  constexpr NoIntersection() : Intersection(-1, Position{}, Direction{}){}
};

}

#endif
