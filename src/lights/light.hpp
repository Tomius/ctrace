#ifndef LIGHTS_HPP_
#define LIGHTS_HPP_

#include "../core/types.hpp"

namespace ctrace {

constexpr Intersection intersectRay(Ray const&);

struct AmbientLight {
  const Color color;
  constexpr AmbientLight(Color const& color) : color{color} {}
};

struct DirectionalLight {
  const Direction dir;
  const Color color;
  constexpr DirectionalLight(Direction const& dir, Color const& color)
      : dir{normalize(dir)}, color{color} {}
};

struct PointLight {
  const Position pos;
  const Color color;
  constexpr PointLight(Position const& pos, Color const& color)
      : pos{pos}, color{color} {}
};

constexpr bool isLit(Position const& point, AmbientLight const& light) {
  return true;
}

constexpr bool isLit(Position const& point, DirectionalLight const& light) {
  Ray shadow_checker = Ray(point + sqrt(kEpsilon)*light.dir, light.dir);
  Intersection shadow_checker_int = intersectRay(shadow_checker);
  return !isValid(shadow_checker_int);
}

constexpr bool isLit(Position const& point, PointLight const& light) {
  Vector point2light = light.pos - point, p2ld = normalize(point2light);
  Ray shadow_checker = Ray(point + sqrt(kEpsilon)*p2ld, p2ld);
  Intersection shadow_checker_int = intersectRay(shadow_checker);
  if(isValid(shadow_checker_int)) {
    return length(point2light) < shadow_checker_int.dist_eye + kEpsilon;
  } else {
    return true;
  }
}

}

#endif
