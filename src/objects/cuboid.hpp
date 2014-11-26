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
  constexpr Cuboid(Material const& material,
                   Vector const& a, Vector const& b,
                   Vector const& d, Vector const& e)
      : c{b+(d-a)}, f{b+(e-a)}, g{c+(e-a)}, h{d+(e-a)}
      , quad0_{material, a, b, c, d} // right
      , quad1_{material, f, e, h, g} // left
      , quad2_{material, a, e, f, b} // up
      , quad3_{material, c, g, h, d} // down
      , quad4_{material, b, f, g, c} // front
      , quad5_{material, a, d, h, e} // back
  {}

  constexpr Intersection intersectRay(Ray const& r) const {
    Intersection closest0 = quad0_.intersectRay(r);
    Intersection closest1 = closerOneOf(quad1_.intersectRay(r), closest0);
    Intersection closest2 = closerOneOf(quad2_.intersectRay(r), closest1);
    Intersection closest3 = closerOneOf(quad3_.intersectRay(r), closest2);
    Intersection closest4 = closerOneOf(quad4_.intersectRay(r), closest3);
    return closerOneOf(quad5_.intersectRay(r), closest4);
  }

  constexpr Material const& material() const { return quad0_.material(); }

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

template<typename Material>
constexpr Cuboid<Material> makeAxisAlignedCuboid(Material const& material,
                                                 Position const& center,
                                                 Vector const& edges) {
  Vector e2 = edges/2;
  return {
    material,
    center+Position{+1, +1, -1}*e2, center+Position{+1, +1, +1}*e2,
    center+Position{+1, -1, -1}*e2, center+Position{-1, +1, -1}*e2
  };
}

}

#endif
