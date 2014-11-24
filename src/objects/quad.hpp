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
                 Position const& c, Position const& d)
      : triangle0_(material, a, b, c), triangle1_(material, a, c, d) {}

  constexpr Intersection intersectRay(Ray const& ray) const {
    return closer_one_of(triangle0_.intersectRay(ray),
                         triangle1_.intersectRay(ray));
  }

  constexpr Material material() const { return triangle0_.material(); }

 private:
  Triangle<Material> triangle0_, triangle1_;
};

template<typename Material>
constexpr Quad<Material> makeQuad(Material const& material,
                                  Position const& a, Position const& b,
                                  Position const& c, Position const& d) {
  return {material, a, b, c, d};
}

}

#endif
