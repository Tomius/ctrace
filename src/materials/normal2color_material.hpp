#ifndef MATERIALS_NORMAL2COLOR_MATERIAL_HPP_
#define MATERIALS_NORMAL2COLOR_MATERIAL_HPP_

#include "../math/vec3.hpp"
#include "../lights/light.hpp"

namespace ctrace {

class Normal2ColorMaterial {
 public:
  constexpr Normal2ColorMaterial() {}

  constexpr Color getColor(Intersection const& intersection,
                           AmbientLight const& light) const {
    return own_color(intersection.normal) * light.color;
  }

  constexpr Color getColor(Intersection const& intersection,
                           DirectionalLight const& light) const {
    if (isLit(intersection.pos, light)) {
      real normal_light_dot = dot(intersection.normal, normalize(light.dir));
      return max(normal_light_dot, 0) * own_color(intersection.normal) * light.color;
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
      return attenuation * intensity * light.color * own_color(intersection.normal);
    } else {
      return Color{};
    }
  }

 private:
  constexpr Color own_color(Direction const& normal) const {
    return (normal+1)/2; // maps [-1, +1] to [0, 1]
  }
};

}

#endif
