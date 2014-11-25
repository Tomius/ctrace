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

  constexpr Intersection intersectRay(Ray const& ray) const {
    Intersection intersection = first_object_.intersectRay(ray);
    return rest_.intersectRay(ray, intersection);
  }

  constexpr Intersection intersectRay(Ray const& ray,
                                      Intersection const& previous) const {
    return closer_one_of(first_object_.intersectRay(ray), previous);
  }

  template <typename LightContainer>
  constexpr Color intersectRay(Ray const& ray,
                               LightContainer const& lights) const {
    Intersection intersection = first_object_.intersectRay(ray);
    return rest_.intersectRay(ray, lights, intersection, first_object_.material());
  }

  template <typename LightContainer, typename Material>
  constexpr Color intersectRay(Ray const& ray,
                               LightContainer const& lights,
                               Intersection const& previous,
                               Material const& material) const {
    Intersection current = first_object_.intersectRay(ray);
    if (is_first_closer(current, previous)) {
      return rest_.intersectRay(ray, lights, current, first_object_.material());
    } else {
      return rest_.intersectRay(ray, lights, previous, material);
    }
  }

 private:
  ObjectContainer<N-1, Rest...> rest_;
  FirstObject first_object_;
};

template<typename Object>
struct ObjectContainer<1, Object> {
 public:
  constexpr ObjectContainer(Object const& object) : object_(object) {}

  constexpr Intersection intersectRay(Ray const& ray) const {
    return object_.intersectRay(ray);
  }

  constexpr Intersection intersectRay(Ray const& ray,
                                      Intersection const& previous) const {
    return closer_one_of(object_.intersectRay(ray), previous);
  }

  template <typename LightContainer>
  constexpr Color intersectRay(Ray const& ray,
                               LightContainer const& lights) const {
    Intersection intersection = object_.intersectRay(ray);
    if (is_valid(intersection)) {
      return lights.calulateLighting(object_.material(), intersection);
    } else {
      return kBackgroundColor;
    }
  }

  template <typename LightContainer, typename Material>
  constexpr Color intersectRay(Ray const& ray,
                               LightContainer const& lights,
                               Intersection const& previous,
                               Material const& material) const {
    Intersection current = object_.intersectRay(ray);
    if (is_first_closer(current, previous)) {
      return lights.calulateLighting(object_.material(), current);
    } else {
      if (is_valid(previous)) {
        return lights.calulateLighting(material, previous);
      } else {
        return kBackgroundColor;
      }
    }
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
