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

  template<typename LightContainer>
  constexpr Fragment intersectRay(Ray const& r,
                                  LightContainer const& lights,
                                  Fragment const& previous) const {
    Fragment previous0 = triangle0_.intersectRay(r, lights, previous);
    return triangle1_.intersectRay(r, lights, previous0);
  }

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
