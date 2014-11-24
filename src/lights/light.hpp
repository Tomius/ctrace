#ifndef LIGHTS_HPP_
#define LIGHTS_HPP_

namespace ctrace {

struct AmbientLight {
  Color color;
  constexpr AmbientLight(Color const& color) : color(color) {}
  constexpr bool isVisible(Position const& point) {
    return true;
  }
};

struct DirectionalLight {
  Direction dir;
  Color color;
  constexpr DirectionalLight(Direction const& dir, Color const& color)
      : dir(dir), color(color) {}
  // constexpr bool isVisible(Position const& point) {
  //   Ray shadow_checker = Ray(inter.pos + 1e-3*dir, dir);
  //   Intersection shadow_checker_int = getClosestIntersection(shadow_checker);
  //   if(shadow_checker_int.is_valid) {
  //     return false;
  //   } else {
  //     return true;
  //   }
  // }
};

struct PointLight {
  Position pos;
  Color color;
  constexpr PointLight(Position const& pos, Color const& color)
      : pos(pos), color(color) {}
  // constexpr bool isVisible(Position const& point) {
  //   return true;
  // }
};

}

#endif
