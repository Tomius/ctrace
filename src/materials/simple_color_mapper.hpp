#ifndef SIMPLE_COLOR_MAPPER_HPP_
#define SIMPLE_COLOR_MAPPER_HPP_

#include "../math/vec3.hpp"

namespace ctrace {

class SimpleColorMapper {
 public:
  constexpr SimpleColorMapper(Color const& color)
    : ambient_(color), diffuse_(color), specular_(color) {}

  constexpr SimpleColorMapper(Color const& ambient,
                              Color const& diffuse,
                              Color const& specular)
    : ambient_(ambient), diffuse_(diffuse), specular_(specular) {}

  constexpr Color ambientColor(Intersection const&) const { return ambient_; }
  constexpr Color diffuseColor(Intersection const&) const { return diffuse_; }
  constexpr Color specularColor(Intersection const&) const { return specular_; }

 private:
  Color ambient_, diffuse_, specular_;
};

}

#endif
