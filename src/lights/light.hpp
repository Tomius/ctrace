#ifndef LIGHTS_HPP_
#define LIGHTS_HPP_

#include "../core/types.hpp"

namespace ctrace {

constexpr Intersection intersectRay(Ray const&);

struct AmbientLight {
  Color color;
  constexpr AmbientLight(Color const& color) : color{color} {}
};

struct DirectionalLight {
  Direction dir;
  Color color;
  constexpr DirectionalLight(Direction const& dir, Color const& color)
      : dir{normalize(dir)}, color{color} {}
};

struct PointLight {
  Position pos;
  Color color;
  constexpr PointLight(Position const& pos, Color const& color)
      : pos{pos}, color{color} {}
};

constexpr bool isLit(Position const& point, AmbientLight const& light) {
  return true;
}

constexpr bool isLit(Position const& point, Direction const& point2light) {
  Ray shadow_checker = Ray(point + kEpsilon*point2light, point2light);
  Intersection shadow_checker_int = intersectRay(shadow_checker);
  if(is_valid(shadow_checker_int)) {
    return false;
  } else {
    return true;
  }
}

constexpr bool isLit(Position const& point, DirectionalLight const& light) {
  return isLit(point, light.dir);
}

constexpr bool isLit(Position const& point, PointLight const& light) {
  return isLit(point, normalize(light.pos - point));
}

}

#endif
