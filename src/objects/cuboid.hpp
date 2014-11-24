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
      , quad0_{material, a, b, c, d} // right
      , quad1_{material, f, e, h, g} // left
      , quad2_{material, a, e, f, b} // up
      , quad3_{material, c, g, h, d} // down
      , quad4_{material, b, f, h, c} // front
      , quad5_{material, a, d, h, e} // back
  {}

  constexpr Intersection intersectRay(Ray const& r) const {
    Intersection closest0 = closer_one_of(quad0_.intersectRay(r),
                                          quad1_.intersectRay(r));
    Intersection closest1 = closer_one_of(quad2_.intersectRay(r), closest0);
    Intersection closest2 = closer_one_of(quad3_.intersectRay(r), closest1);
    Intersection closest3 = closer_one_of(quad4_.intersectRay(r), closest2);
    return closer_one_of(quad5_.intersectRay(r), closest3);
  }

  constexpr Material material() const { return quad0_.material(); }

 private:
  // Calculated values
  Position c, f, g, h;

  // who needs arrays anyways...
  Quad<Material> quad0_, quad1_, quad2_, quad3_, quad4_, quad5_;
};

template<typename Material>
constexpr Cuboid<Material> makeCuboid(Material const& material,
                                      Position const& a, Position const& b,
                                      Position const& d, Position const& e) {
  return {material, a, b, d, e};
}

}

#endif
