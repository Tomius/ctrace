#ifndef MATERIALS_SIMPLE_MATERIAL_HPP_
#define MATERIALS_SIMPLE_MATERIAL_HPP_

#include "../math/vec3.hpp"

namespace ctrace {

struct SimpleMaterial {
  vec3 color;
  constexpr SimpleMaterial(vec3 const& color) : color(color) {}

  constexpr vec3 getColor(vec3 const& pos, vec3 const& normal) const {
    vec3 fake_light_dir{-1.2, 1, -0.8};
    return (max(dot(normal, normalize(fake_light_dir)), 0) + 0.1f) * color;
  }
};

}

#endif
