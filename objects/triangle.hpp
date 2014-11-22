#ifndef OBJECTS_TRIANGLE_HPP_
#define OBJECTS_TRIANGLE_HPP_

#include "../core/types.hpp"

namespace ctrace {

template<typename Material>
struct Triangle {
 public:
  // The points of the triangle are understood in CCW order
  constexpr Triangle(Material const& material,
                     Vector const& a, Vector const& b, Vector const& c)
    : material{material}, a{a}, b{b}, c{c} {
      Vector ab = b - a;
      Vector ac = c - a;
      normal = normalize(cross(normalize(ab), normalize(ac)));
  }

  template<typename LightContainer>
  constexpr Fragment intersectRay(Ray const& r, LightContainer const& lights,
                                  Fragment const& previous) const {
    real divisor = dot(r.direction, normal);
    if (divisor == 0.0f) {
      return previous;
    }

    real ray_travel_dist = dot(a - r.origin, normal) / divisor;
    if(ray_travel_dist < 0 || (0 < previous.distance_from_eye &&
        previous.distance_from_eye < ray_travel_dist)) {
      return previous;
    }

    Vector plane_intersection = r.origin + ray_travel_dist * r.direction;

    const Vector& x = plane_intersection;
    Vector ab = b - a, ax = x - a;
    Vector bc = c - b, bx = x - b;
    Vector ca = a - c, cx = x - c;

    if(dot(cross(ab, ax), normal) >= 0)
      if(dot(cross(bc, bx), normal) >= 0)
        if(dot(cross(ca, cx), normal) >= 0)
          return Fragment{ray_travel_dist,
                          lights.calulateLighting(material, x, normal)};

    return previous;
  }

 private:
  Material material;
  Vector a, b, c, normal;
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
