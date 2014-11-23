#ifndef OBJECTS_TRIANGLE_HPP_
#define OBJECTS_TRIANGLE_HPP_

#include "../core/types.hpp"

namespace ctrace {

template<typename Material>
struct Triangle {
 public:
  // The points of the triangle are understood in CCW order
  constexpr Triangle(Material const& material,
                     Position const& a, Position const& b, Position const& c)
      : material_{material}, a_{a}, b_{b}, c_{c} {
    Direction ab = b_ - a_;
    Direction ac = c_ - a_;
    normal_ = normalize(cross(normalize(ab), normalize(ac)));
  }

  template<typename LightContainer>
  constexpr Fragment intersectRay(Ray const& r,
                                  LightContainer const& lights,
                                  Fragment const& previous) const {
    real divisor = dot(r.direction, normal_);
    if (divisor == 0.0f) {
      return previous;
    }

    real ray_travel_dist = dot(a_ - r.origin, normal_) / divisor;
    if(ray_travel_dist < 0 || (0 < previous.distance_from_eye &&
        previous.distance_from_eye < ray_travel_dist)) {
      return previous;
    }

    Position plane_intersection = r.origin + ray_travel_dist * r.direction;

    const Position& x = plane_intersection;
    Direction ab = b_ - a_, ax = x - a_;
    Direction bc = c_ - b_, bx = x - b_;
    Direction ca = a_ - c_, cx = x - c_;

    if(dot(cross(ab, ax), normal_) >= 0)
      if(dot(cross(bc, bx), normal_) >= 0)
        if(dot(cross(ca, cx), normal_) >= 0)
          return Fragment{ray_travel_dist,
                          lights.calulateLighting(material_, x, normal_)};

    return previous;
  }

 private:
  Material material_;
  Position a_, b_, c_;
  Direction normal_;
};

template<typename Material>
constexpr Triangle<Material> makeTriangle(Material const& material,
                                          Vector const& a,
                                          Vector const& b,
                                          Vector const& c) {
  return {material, a, b, c};
}

}

#endif
