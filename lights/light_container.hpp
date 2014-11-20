#ifndef LIGHT_CONTAINTER_HPP_
#define LIGHT_CONTAINTER_HPP_

#include "../core/types.hpp"

namespace ctrace {

template<int N, typename T, typename... Args>
class LightContainer {
 public:
  constexpr LightContainer(T const& current,
                            LightContainer<N-1, Args...> const& contained)
    : current(current), contained(contained) {}

  // not quite OO, but it's easier this way
  template<typename Material>
  constexpr Color calulateLighting(Material const& material,
                                   Color const& pos, Color const& normal) const {
    return material.getColor(pos, normal, current)
           + contained.calulateLighting(material, pos, normal);
  }

 private:
  LightContainer<N-1, Args...> contained;
  T current;
};

template<typename T>
class LightContainer<1, T> {
 public:
  constexpr LightContainer(T const& current) : current(current) {}

  template<typename Material>
  constexpr Color calulateLighting(Material const& material,
                                   Color const& pos, Color const& normal) const {
    return material.getColor(pos, normal, current);
  }

 private:
  T current;
};

template<typename T, typename... Args>
constexpr LightContainer<sizeof...(Args)+1, T, Args...>
makeLightContainer(T const& first, Args const&... args) {
  return {first, makeLightContainer(args...)};
}

template<typename T>
constexpr LightContainer<1, T> makeLightContainer(T const& value) {
  return {value};
}

}

#endif
