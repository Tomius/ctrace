#ifndef OBJECTS_TRIANGLE_HPP_
#define OBJECTS_TRIANGLE_HPP_

#include <climits>
#include "../core/types.hpp"

namespace ctrace {

template<typename Material>
struct Triangle {
  Material material;
  vec3 a, b, c, normal;

  // CCW
  constexpr Triangle(Material const& material,
                     vec3 const& a, vec3 const& b, vec3 const& c)
    : material(material), a(a), b(b), c(c) {
      vec3 ab = b - a;
      vec3 ac = c - a;
      normal = normalize(cross(normalize(ab), normalize(ac)));
  }

  constexpr Fragment intersectRay(Ray r, Fragment const& previous) const {
    float divisor = dot(r.direction, normal);
    if (divisor == 0.0f) {
      return previous;
    }

    float ray_travel_dist = dot(a - r.origin, normal) / divisor;
    if(ray_travel_dist < 0.0f) {
      return previous;
    }

    vec3 plane_intersection = r.origin + ray_travel_dist * r.direction;

    const vec3& x = plane_intersection;

    vec3 ab = b - a;
    vec3 ax = x - a;

    vec3 bc = c - b;
    vec3 bx = x - b;

    vec3 ca = a - c;
    vec3 cx = x - c;

    if(dot(cross(ab, ax), normal) >= 0)
      if(dot(cross(bc, bx), normal) >= 0)
        if(dot(cross(ca, cx), normal) >= 0)
          return handleIntersection(ray_travel_dist, x, normal, previous);


    return previous;
  }

  constexpr Fragment handleIntersection(float ray_travel_dist,
                                        vec3 const& pos,
                                        vec3 const& normal,
                                        Fragment const& previous) const {
    if (0 < previous.distance_from_eye &&
        previous.distance_from_eye < ray_travel_dist) {
      return previous;
    } else {
      return Fragment{ray_travel_dist, material.getColor(pos, normal)};
    }
  }
};

template<typename Material>
constexpr Triangle<Material> makeTriangle(Material const& material, vec3 const& a,
                                          vec3 const& b, vec3 const& c) {
  return {material, a, b, c};
}

}

#endif
