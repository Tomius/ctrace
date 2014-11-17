#ifndef OBJECTS_OBJECTS_HPP_
#define OBJECTS_OBJECTS_HPP_

#include <utility>
#include "../core/types.hpp"

namespace ctrace {

template<int N, typename T, typename... Args>
struct Objects {
  Objects<N-1, Args...> contained;
  T current;

  constexpr Objects(T const& current, Objects<N-1, Args...> const& contained)
    : current(current), contained(contained) {}

  constexpr Fragment intersectRay(Ray const& ray,
                                  Fragment const& previous) const {
    return contained.intersectRay(ray, current.intersectRay(ray, previous));
  }
};

template<typename T>
struct Objects<1, T> {
  T current;

  constexpr Objects(T const& current) : current(current) {}

  constexpr Fragment intersectRay(Ray const& ray,
                                  Fragment const& previous) const {
    return current.intersectRay(ray, previous);
  }
};

template<typename T, typename... Args>
constexpr Objects<sizeof...(Args)+1, T, Args...> makeObjects(T const& first,
                                                             Args const&... args) {
    return {first, makeObjects(args...)};
}

template<typename T>
constexpr Objects<1, T> makeObjects(T const& value) {
    return {value};
}

}

#endif
