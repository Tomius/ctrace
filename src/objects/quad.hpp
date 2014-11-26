#ifndef OBJECTS_QUAD_HPP_
#define OBJECTS_QUAD_HPP_

#include "./triangle.hpp"

namespace ctrace {

template<typename Material>
class Quad {
 public:
  // the winding order of the first triangle should be CCW
  constexpr Quad(Material const& material,
                 Position const& a, Position const& b,
                 Position const& c, Position const& d,
                 bool ccw = true)
      : triangle0_(material, a, b, c, ccw)
      , triangle1_(material, a, c, d, ccw) {}

  constexpr Intersection intersectRay(Ray const& ray) const {
    return closerOneOf(triangle0_.intersectRay(ray),
                       triangle1_.intersectRay(ray));
  }

  constexpr Material material() const { return triangle0_.material(); }

 private:
  Triangle<Material> triangle0_, triangle1_;
};

template<typename Material>
constexpr Quad<Material> makeQuad(Material const& material,
                                  Position const& a, Position const& b,
                                  Position const& c, Position const& d,
                                  bool ccw = true) {
  return {material, a, b, c, d, ccw};
}

}

#endif
