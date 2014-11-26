#ifndef MATERIALS_DIFFUSE_MATERIAL_HPP_
#define MATERIALS_DIFFUSE_MATERIAL_HPP_

#include "../math/vec3.hpp"
#include "../lights/light.hpp"

namespace ctrace {

class DiffuseMaterial {
 public:
  constexpr DiffuseMaterial(Color const& color) : own_color_(color) {}

  constexpr Color getColor(Intersection const& intersection,
                           AmbientLight const& light) const {
    return own_color_ * light.color;
  }

  constexpr Color getColor(Intersection const& intersection,
                           DirectionalLight const& light) const {
    if (isLit(intersection.pos, light)) {
      real normal_light_dot = dot(intersection.normal, normalize(light.dir));
      return max(normal_light_dot, 0) * own_color_ * light.color;
    } else {
      return Color{};
    }
  }

  constexpr Color getColor(Intersection const& intersection,
                           PointLight const& light) const {
    if (isLit(intersection.pos, light)) {
      Direction pos_to_light = light.pos - intersection.pos;
      real attenuation = square(1/length(pos_to_light));
      real normal_light_dot = dot(intersection.normal, normalize(pos_to_light));
      real intensity = max(normal_light_dot, 0);
      return attenuation * intensity * light.color * own_color_;
    } else {
      return Color{};
    }
  }

 private:
  Color own_color_;
};

}

#endif
