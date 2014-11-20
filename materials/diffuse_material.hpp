#ifndef MATERIALS_DIFFUSE_MATERIAL_HPP_
#define MATERIALS_DIFFUSE_MATERIAL_HPP_

#include "../math/vec3.hpp"
#include "../lights/light.hpp"

namespace ctrace {

class DiffuseMaterial {
 public:
  constexpr DiffuseMaterial(Color const& color,
                            bool double_sided = false)
      : own_color(color), double_sided(double_sided) {}

  constexpr Color getColor(Color const&, Color const&,
                           AmbientLight const& light) const {
    return own_color * light.color;
  }

  constexpr Color getColor(Color const& pos, Color const& normal,
                           DirectionalLight const& light) const {
    float normal_light_dot = dot(normal, normalize(light.dir));
    if (double_sided) {
      return abs(normal_light_dot) * own_color;
    } else {
      return max(normal_light_dot, 0) * own_color;
    }
  }

  constexpr Color getColor(Color const& pos, Color const& normal,
                           PointLight const& light) const {
    Vector pos_to_light = light.pos - pos;
    float attenuation = square(1/length(pos_to_light));
    float normal_light_dot = dot(normal, normalize(pos_to_light));
    float intensity =
        double_sided ? abs(normal_light_dot) : max(normal_light_dot, 0);
    return attenuation * intensity * light.color * own_color;
  }

 private:
  Color own_color;
  bool double_sided;
};

}

#endif
