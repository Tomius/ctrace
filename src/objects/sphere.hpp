#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "../core/types.hpp"

namespace ctrace {

template<typename Material>
class Sphere {
 public:
  constexpr Sphere(Material const& material, Position const& center, real radius)
      : material_(material), center_(center), radius_(radius) {}

  constexpr Intersection intersectRay(Ray const& ray) const {
    // a simple quadratic equtions for the ray_travel_dist
    Direction c2o = ray.origin - center_;
    real a = dot(ray.direction, ray.direction);
    real b = 2 * dot(ray.direction, c2o);
    real c = dot(c2o, c2o) - radius_*radius_;

    real det = b*b - 4*a*c;
    if (det < 0) {
      return NoIntersection{};;
    }

    real t1 = (-b + sqrt(det)) / (2*a);
    real t2 = (-b - sqrt(det)) / (2*a);
    real ray_travel_dist = min(t1, t2);

    if (ray_travel_dist < 0) {
      return NoIntersection{};
    }

    Position pos = ray.origin + ray_travel_dist*ray.direction;
    Direction normal = normalize(pos - center_);
    Direction lighting_normal =
        dot(ray.direction, normal) > 0 ? -1*normal : normal;

    return Intersection{ray_travel_dist, pos, lighting_normal};
  }

  constexpr Material const& material() const { return material_; }

 private:
  const Material material_;
  const Position center_;
  const real radius_;
};


template<typename Material>
constexpr Sphere<Material> makeSphere(Material const& material,
                                      Position const& center, real radius) {
  return {material, center, radius};
}

}

#endif
