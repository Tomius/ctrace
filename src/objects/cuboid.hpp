#ifndef OBJECTS_CUBOID_HPP_
#define OBJECTS_CUBOID_HPP_

#include "./quad.hpp"

namespace ctrace {

// Parallelepiped is basically a cuboid, but the
// edges do not have to be parrallel to each other.
template<typename Material>
class Parallelepiped {
 public:

  // A special case of the Parallelepiped is the cube. Use this ascii art as
  // reference to understand the algorithm that works on general Parallelepipeds.
  //
  //                          (E)-----(A)
  //                          /|      /|
  //                         / |     / |
  //                       (F)-----(B) |
  //                        | (H)---|-(D)
  //                        | /     | /
  //                        |/      |/
  //                       (G)-----(C)
  //
  constexpr Parallelepiped(Material const& material,
                           Position const& origin, // point H on the ascii art.
                           Direction const& x_axis_edge, // H -> D vector
                           Direction const& y_axis_edge, // H -> E vector
                           Direction const& z_axis_edge) // H -> G vector
      : a_{origin + x_axis_edge + y_axis_edge}
      , b_{origin + x_axis_edge + y_axis_edge + z_axis_edge}
      , c_{origin + x_axis_edge + z_axis_edge}
      , d_{origin + x_axis_edge}
      , e_{origin + y_axis_edge}
      , f_{origin + y_axis_edge + z_axis_edge}
      , g_{origin + z_axis_edge}
      , h_{origin}
      , quad0_{material, a_, b_, c_, d_} // right
      , quad1_{material, f_, e_, h_, g_} // left
      , quad2_{material, a_, e_, f_, b_} // up
      , quad3_{material, c_, g_, h_, d_} // down
      , quad4_{material, b_, f_, g_, c_} // front
      , quad5_{material, a_, d_, h_, e_} // back
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
  // calculated values needed only to initialize the quads.
  const Position a_, b_, c_, d_, e_, f_, g_, h_;

  // Who needs arrays anyways...
  const Quad<Material> quad0_, quad1_, quad2_, quad3_, quad4_, quad5_;
};

template<typename Material>
constexpr Parallelepiped<Material>
 makeParallelepiped(Material const& material, Position const& origin,
                    Direction const& x_axis_edge, Direction const& y_axis_edge,
                    Direction const& z_axis_edge) {
  return {material, origin, x_axis_edge, y_axis_edge, z_axis_edge};
}

template<typename Material>
constexpr Parallelepiped<Material> makeAxisAlignedCuboid(
      Material const& material, Position const& center, Vector const& edges) {
  return {material, center-edges/2, kAxisX*edges, kAxisY*edges, kAxisZ*edges};
}

}

#endif
