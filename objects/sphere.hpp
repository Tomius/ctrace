#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "../core/types.hpp"

namespace ctrace {

template<typename Material>
class Sphere {
 public:
  constexpr Sphere(Material const& material, Position const& center, real radius)
      : material_(material), center_(center), radius_(radius) {}

  template<typename LightContainer>
  constexpr Fragment intersectRay(Ray const& ray,
                                  LightContainer const& lights,
                                  Fragment const& previous) const {
    // a simple quadratic equtions for the ray_travel_dist
    Direction c2o = ray.origin - center_;
    real a = dot(ray.direction, ray.direction);
    real b = 2 * dot(ray.direction, c2o);
    real c = dot(c2o, c2o) - radius_*radius_;

    real det = b*b - 4*a*c;
    if (det < 0) return previous;

    real t1 = (-b + sqrt(det)) / (2*a);
    real t2 = (-b - sqrt(det)) / (2*a);
    real ray_travel_dist = min(t1, t2);

    // if the current fragment is behind the eye (not visible),
    // or the prev fragment is valid, and is closer to the
    // eye than this one, then return that.
    if (ray_travel_dist < 0 || (0 < previous.distance_from_eye &&
        previous.distance_from_eye < ray_travel_dist)) {
      return previous;
    }

    Position pos = ray.origin + ray_travel_dist*ray.direction;
    Direction normal = normalize(pos - center_);

    return Fragment{ray_travel_dist,
                    lights.calulateLighting(material_, pos, normal)};
  }

 private:
  Material material_;
  Position center_;
  real radius_;
};


template<typename Material>
constexpr Sphere<Material> makeSphere(Material const& material,
                                      Position const& center, real radius) {
  return {material, center, radius};
}

}

#endif
