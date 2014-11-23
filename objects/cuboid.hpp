#ifndef OBJECTS_CUBOID_HPP_
#define OBJECTS_CUBOID_HPP_

#include "./quad.hpp"

namespace ctrace {

template<typename Material>
class Cuboid {
 public:

  /*       (E)-----(A)
           /|      /|
          / |     / |
        (F)-----(B) |
         | (H)---|-(D)
         | /     | /
         |/      |/
        (G)-----(C)        */

  // The normals are facing outwards.
  // If you need inward facing normals, use double-sided material.
  constexpr Cuboid(Material const& material,
                   Vector const& a, Vector const& b,
                   Vector const& d, Vector const& e)
      : c{b+(d-a)}, f{b+(e-a)}, g{c+(e-a)}, h{d+(e-a)}
      , quad0{material, a, b, c, d} // right
      , quad1{material, f, e, h, g} // left
      , quad2{material, a, e, f, b} // up
      , quad3{material, c, g, h, d} // down
      , quad4{material, b, f, h, c} // front
      , quad5{material, a, d, h, e} // back
  {}

  template<typename LightContainer>
  constexpr Fragment intersectRay(Ray const& r, LightContainer const& lights,
                                  Fragment const& previous) const {
    Fragment previous0 = quad0.intersectRay(r, lights, previous);
    Fragment previous1 = quad1.intersectRay(r, lights, previous0);
    Fragment previous2 = quad2.intersectRay(r, lights, previous1);
    Fragment previous3 = quad3.intersectRay(r, lights, previous2);
    Fragment previous4 = quad4.intersectRay(r, lights, previous3);
    return quad5.intersectRay(r, lights, previous4);
  }

 private:
  // Calculated values
  Position c, f, g, h;

  // who needs arrays anyways...
  Quad<Material> quad0, quad1, quad2, quad3, quad4, quad5;
};

template<typename Material>
constexpr Cuboid<Material> makeCuboid(Material const& material,
                                      Position const& a, Position const& b,
                                      Position const& d, Position const& e) {
  return {material, a, b, d, e};
}

}

#endif
