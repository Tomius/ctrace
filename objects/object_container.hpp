#ifndef OBJECTS_OBJECT_CONTAINER_HPP_
#define OBJECTS_OBJECT_CONTAINER_HPP_

#include <utility>
#include "../core/types.hpp"

namespace ctrace {

template<int N, typename FirstObject, typename... Rest>
class ObjectContainer {
 public:
  constexpr ObjectContainer(FirstObject const& first_object,
                            ObjectContainer<N-1, Rest...> const& rest)
    : rest_(rest), first_object_(first_object) {}

  // Not quite a KD-tree
  template <typename LightContainer>
  constexpr Fragment intersectRay(Ray const& ray,
                                  LightContainer const& lights,
                                  Fragment const& previous) const {
    Fragment previous2 = first_object_.intersectRay(ray, lights, previous);
    return rest_.intersectRay(ray, lights, previous2);
  }

 private:
  ObjectContainer<N-1, Rest...> rest_;
  FirstObject first_object_;
};

template<typename Object>
struct ObjectContainer<1, Object> {
 public:
  constexpr ObjectContainer(Object const& object) : object_(object) {}

  template <typename LightContainer>
  constexpr Fragment intersectRay(Ray const& ray,
                                  LightContainer const& lights,
                                  Fragment const& previous) const {
    return object_.intersectRay(ray, lights, previous);
  }

 private:
  Object object_;
};

template<typename FirstObject, typename... Rest>
constexpr ObjectContainer<sizeof...(Rest)+1, FirstObject, Rest...>
makeObjectContainer(FirstObject const& first_object, Rest const&... rest) {
  return {first_object, makeObjectContainer(rest...)};
}

template<typename Object>
constexpr ObjectContainer<1, Object> makeObjectContainer(Object const& object) {
  return {object};
}

}

#endif
