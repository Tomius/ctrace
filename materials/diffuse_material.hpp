#ifndef MATERIALS_DIFFUSE_MATERIAL_HPP_
#define MATERIALS_DIFFUSE_MATERIAL_HPP_

#include "../math/vec3.hpp"
#include "../lights/light.hpp"

namespace ctrace {

struct DiffuseMaterial {
  Color own_color;
  constexpr DiffuseMaterial(Color const& color) : own_color(color) {}

  constexpr Color getColor(Color const&, Color const&,
                           AmbientLight const& light) const {
    return own_color * light.color;
  }

  constexpr Color getColor(Color const& pos, Color const& normal,
                           DirectionalLight const& light) const {
    return max(dot(normal, normalize(light.dir)), 0) * own_color;
  }

  constexpr Color getColor(Color const& pos, Color const& normal,
                           PointLight const& light) const {
    Vector pos_to_light = light.pos - pos;
    float attenuation = square(1/length(pos_to_light));
    float intensity = max(dot(normal, normalize(pos_to_light)), 0.0f);
    return attenuation * intensity * light.color * own_color;
  }
};

}

#endif
