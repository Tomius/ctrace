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
                   Vector const& d, Vector const& e,
                   bool outwards_normals = true)
      : c{b+(d-a)}, f{b+(e-a)}, g{c+(e-a)}, h{d+(e-a)}
      , quad0_{material, a, b, c, d, outwards_normals} // right
      , quad1_{material, f, e, h, g, outwards_normals} // left
      , quad2_{material, a, e, f, b, outwards_normals} // up
      , quad3_{material, c, g, h, d, outwards_normals} // down
      , quad4_{material, b, f, g, c, outwards_normals} // front
      , quad5_{material, a, d, h, e, outwards_normals} // back
  {}

  constexpr Intersection intersectRay(Ray const& r) const {
    Intersection closest0 = quad0_.intersectRay(r);
    Intersection closest1 = closerOneOf(quad1_.intersectRay(r), closest0);
    Intersection closest2 = closerOneOf(quad2_.intersectRay(r), closest1);
    Intersection closest3 = closerOneOf(quad3_.intersectRay(r), closest2);
    Intersection closest4 = closerOneOf(quad4_.intersectRay(r), closest3);
    return closerOneOf(quad5_.intersectRay(r), closest4);
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
                                      Position const& d, Position const& e,
                                      bool outwards_normals = true) {
  return {material, a, b, d, e, outwards_normals};
}

template<typename Material>
constexpr Cuboid<Material> makeAxisAlignedCuboid(Material const& material,
                                                 Position const& center,
                                                 Vector const& edges,
                                                 bool outwards_normals = true) {
  Vector e2 = edges/2;
  return {
    material,
    center+Position{+1, +1, -1}*e2, center+Position{+1, +1, +1}*e2,
    center+Position{+1, -1, -1}*e2, center+Position{-1, +1, -1}*e2,
    outwards_normals
  };
}

}

#endif
