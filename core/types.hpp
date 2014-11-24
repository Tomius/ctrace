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

constexpr bool is_valid(Intersection const& inter) {
  return inter.dist_eye >= 0;
}

constexpr bool is_first_closer(Intersection const& a,
                               Intersection const& b) {
  return is_valid(a) && (!is_valid(b) || a.dist_eye < b.dist_eye);
}

constexpr Intersection closer_one_of(Intersection const& a,
                                     Intersection const& b) {
  return is_first_closer(a, b) ? a : b;
}

struct NoIntersection : public Intersection {
  constexpr NoIntersection() : Intersection(-1, Position{}, Direction{}){}
};

}

#endif
