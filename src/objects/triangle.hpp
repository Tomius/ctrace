#ifndef OBJECTS_TRIANGLE_HPP_
#define OBJECTS_TRIANGLE_HPP_

#include "../core/types.hpp"

namespace ctrace {

template<typename Material>
struct Triangle {
 public:
  constexpr Triangle(Material const& material,
                     Position const& a, Position const& b, Position const& c,
                     bool ccw = true)
      : material_{material}, a_{a}, b_{ccw ? b : c}, c_{ccw ? c : b} {
    Direction ab = b_ - a_;
    Direction ac = c_ - a_;
    normal_ = normalize(cross(normalize(ab), normalize(ac)));
  }

  constexpr Intersection intersectRay(Ray const& ray) const {
    real divisor = dot(ray.direction, normal_);
    if (abs(divisor) < kEpsilon) {
      return NoIntersection{};
    }

    real ray_travel_dist = dot(a_ - ray.origin, normal_) / divisor;
    if (ray_travel_dist < 0) {
      return NoIntersection{};
    }

    Position plane_intersection = ray.origin + ray_travel_dist * ray.direction;

    const Position& x = plane_intersection;
    Direction ab = b_ - a_, ax = x - a_;
    Direction bc = c_ - b_, bx = x - b_;
    Direction ca = a_ - c_, cx = x - c_;

    if(dot(cross(ab, ax), normal_) >= 0)
      if(dot(cross(bc, bx), normal_) >= 0)
        if(dot(cross(ca, cx), normal_) >= 0)
          return Intersection{ray_travel_dist, x, normal_};

    return NoIntersection{};
  }

  constexpr Material material() const { return material_; }

 private:
  Material material_;
  Position a_, b_, c_;
  Direction normal_;
};

template<typename Material>
constexpr Triangle<Material> makeTriangle(Material const& material,
                                          Vector const& a, Vector const& b,
                                          Vector const& c, bool ccw = true) {
  return {material, a, b, c, ccw};
}

}

#endif
