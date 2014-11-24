#ifndef LIGHT_CONTAINTER_HPP_
#define LIGHT_CONTAINTER_HPP_

#include "../core/types.hpp"

namespace ctrace {

template<int N, typename FirstLight, typename... Rest>
class LightContainer {
 public:
  constexpr LightContainer(FirstLight const& first_light,
                           LightContainer<N-1, Rest...> const& rest)
    : rest_(rest), first_light_(first_light) {}

  template<typename Material>
  constexpr Color calulateLighting(Material const& material,
                                   Intersection const& intersection) const {
    // the effects of the individual lights are independent, and additive
    return material.getColor(intersection, first_light_)
           + rest_.calulateLighting(material, intersection);
  }

 private:
  LightContainer<N-1, Rest...> rest_;
  FirstLight first_light_;
};

template<typename Light>
class LightContainer<1, Light> {
 public:
  constexpr LightContainer(Light const& light) : light_(light) {}

  template<typename Material>
  constexpr Color calulateLighting(Material const& material,
                                   Intersection const& intersection) const {
    return material.getColor(intersection, light_);
  }

 private:
  Light light_;
};

template<typename FirstLight, typename... Rest>
constexpr LightContainer<sizeof...(Rest)+1, FirstLight, Rest...>
makeLightContainer(FirstLight const& first_light, Rest const&... rest) {
  return {first_light, makeLightContainer(rest...)};
}

template<typename Light>
constexpr LightContainer<1, Light> makeLightContainer(Light const& light) {
  return {light};
}

}

#endif
