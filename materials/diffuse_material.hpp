#ifndef MATERIALS_DIFFUSE_MATERIAL_HPP_
#define MATERIALS_DIFFUSE_MATERIAL_HPP_

#include "../math/vec3.hpp"
#include "../lights/light.hpp"

namespace ctrace {

class DiffuseMaterial {
 public:
  constexpr DiffuseMaterial(Color const& color,
                            bool double_sided = false)
      : own_color_(color), double_sided_(double_sided) {}

  constexpr Color getColor(Intersection const& intersection,
                           AmbientLight const& light) const {
    return own_color_ * light.color;
  }

  constexpr Color getColor(Intersection const& intersection,
                           DirectionalLight const& light) const {
    real normal_light_dot = dot(intersection.normal, normalize(light.dir));
    if (double_sided_) {
      return abs(normal_light_dot) * own_color_ * light.color;
    } else {
      return max(normal_light_dot, 0) * own_color_ * light.color;
    }
  }

  constexpr Color getColor(Intersection const& intersection,
                           PointLight const& light) const {
    Direction pos_to_light = light.pos - intersection.pos;
    real attenuation = square(1/length(pos_to_light));
    real normal_light_dot = dot(intersection.normal, normalize(pos_to_light));
    real intensity =
        double_sided_ ? abs(normal_light_dot) : max(normal_light_dot, 0);
    return attenuation * intensity * light.color * own_color_;
  }

 private:
  Color own_color_;
  bool double_sided_;
};

}

#endif
