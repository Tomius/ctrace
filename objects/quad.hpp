#ifndef OBJECTS_QUAD_HPP_
#define OBJECTS_QUAD_HPP_

#include "./triangle.hpp"

namespace ctrace {

template<typename Material>
class Quad {
 public:
  // the winding order of the first triangle should be CCW
  constexpr Quad(Material const& material,
                  Vector const& a, Vector const& b,
                  Vector const& c, Vector const& d)
      : triangle0(material, a, b, c), triangle1(material, a, c, d) {}

  template<typename LightContainer>
  constexpr Fragment intersectRay(Ray const& r, LightContainer const& lights,
                                  Fragment const& previous) const {
    Fragment previous0 = triangle0.intersectRay(r, lights, previous);
    return triangle1.intersectRay(r, lights, previous0);
  }

 private:
  Triangle<Material> triangle0, triangle1;
};

template<typename Material>
constexpr Quad<Material> makeQuad(Material const& material,
                                  Vector const& a, Vector const& b,
                                  Vector const& c, Vector const& d) {
  return {material, a, b, c, d};
}

}

#endif
