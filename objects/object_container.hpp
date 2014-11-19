#ifndef OBJECTS_OBJECT_CONTAINER_HPP_
#define OBJECTS_OBJECT_CONTAINER_HPP_

#include <utility>
#include "../core/types.hpp"

namespace ctrace {

template<int N, typename T, typename... Args>
struct ObjectContainer {
  ObjectContainer<N-1, Args...> contained;
  T current;

  constexpr ObjectContainer(T const& current,
                            ObjectContainer<N-1, Args...> const& contained)
    : current(current), contained(contained) {}

  template <typename LightContainer>
  constexpr Fragment intersectRay(Ray const& ray, LightContainer const& lights,
                                  Fragment const& previous) const {
    return contained.intersectRay(ray, lights,
                                  current.intersectRay(ray, lights, previous));
  }
};

template<typename T>
struct ObjectContainer<1, T> {
  T current;

  constexpr ObjectContainer(T const& current) : current(current) {}

  template <typename LightContainer>
  constexpr Fragment intersectRay(Ray const& ray, LightContainer const& lights,
                                  Fragment const& previous) const {
    return current.intersectRay(ray, lights, previous);
  }
};

template<typename T, typename... Args>
constexpr ObjectContainer<sizeof...(Args)+1, T, Args...>
makeObjectContainer(T const& first, Args const&... args) {
  return {first, makeObjectContainer(args...)};
}

template<typename T>
constexpr ObjectContainer<1, T> makeObjectContainer(T const& value) {
  return {value};
}

}

#endif
