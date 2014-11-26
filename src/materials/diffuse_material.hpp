#ifndef MATERIALS_DIFFUSE_MATERIAL_HPP_
#define MATERIALS_DIFFUSE_MATERIAL_HPP_

#include "../math/vec3.hpp"
#include "../lights/light.hpp"
#include "./simple_color_mapper.hpp"
#include "./normal_vector_color_mapper.hpp"

namespace ctrace {

template <typename ColorMapper = SimpleColorMapper>
class DiffuseMaterial {
 public:
  constexpr DiffuseMaterial(ColorMapper const& color_mapper)
    : color_mapper_(color_mapper) {}

  constexpr Color getColor(Intersection const& intersection,
                           AmbientLight const& light) const {
    return color_mapper_.ambientColor(intersection) * light.color;
  }

  constexpr Color getColor(Intersection const& intersection,
                           DirectionalLight const& light) const {
    if (isLit(intersection.pos, light)) {
      real normal_light_dot = dot(intersection.normal, normalize(light.dir));
      Color diffuseColor = color_mapper_.diffuseColor(intersection);
      return max(normal_light_dot, 0) * diffuseColor * light.color;
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
      Color diffuseColor = color_mapper_.diffuseColor(intersection);
      return attenuation * intensity * light.color * diffuseColor;
    } else {
      return Color{};
    }
  }

 private:
  ColorMapper color_mapper_;
};

template <typename ColorMapper = SimpleColorMapper>
constexpr DiffuseMaterial<ColorMapper>
makeDiffuseMaterial(ColorMapper const& color_mapper) {
  return {color_mapper};
}

}

#endif
