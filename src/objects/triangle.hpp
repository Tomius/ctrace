#ifndef OBJECTS_TRIANGLE_HPP_
#define OBJECTS_TRIANGLE_HPP_

#include "../core/types.hpp"

namespace ctrace {

template<typename Material>
struct Triangle {
 public:
  constexpr Triangle(Material const& material,
                     Position const& a, Position const& b, Position const& c)
      : material_{material}, a_{a}, b_{b}, c_{c}
      , normal_{normalize(cross(normalize(b_ - a_), normalize(c_ - a_)))} {}

  constexpr Intersection intersectRay(Ray const& ray) const {
    real divisor = dot(ray.direction, normal_);
    if (abs(divisor) < kEpsilon) {
      return NoIntersection{};
    }

    real ray_travel_dist = dot(a_ - ray.origin, normal_) / divisor;
    if (ray_travel_dist < 0) {
      return NoIntersection{};
    }

    Position plane_intersection = ray.origin + ray_travel_dist*ray.direction;

    const Position& x = plane_intersection;
    Direction ab = b_ - a_, ax = x - a_;
    Direction bc = c_ - b_, bx = x - b_;
    Direction ca = a_ - c_, cx = x - c_;

    if(dot(cross(ab, ax), normal_) >= 0)
      if(dot(cross(bc, bx), normal_) >= 0)
        if(dot(cross(ca, cx), normal_) >= 0) {
          Direction lighting_normal = divisor > 0 ? -1*normal_ : normal_;
          return Intersection{ray_travel_dist, x, lighting_normal};
        }

    return NoIntersection{};
  }

  constexpr Material const& material() const { return material_; }

 private:
  const Material material_;
  const Position a_, b_, c_;
  const Direction normal_;
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
