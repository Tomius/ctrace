#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "./types.hpp"

namespace ctrace {

template <typename ObjectContainer, typename LightContainer>
struct Scene {
  ObjectContainer objects;
  LightContainer lights;
  constexpr Scene(ObjectContainer const& objects,
                  LightContainer const& lights)
    : objects(objects), lights(lights) {}

  constexpr Color shootRay(Ray const& ray) const {
    return toneMap(objects.intersectRay(ray, lights, Fragment{}).color);
  }
};

template <typename ObjectContainer, typename LightContainer>
constexpr Scene<ObjectContainer, LightContainer>
makeScene(ObjectContainer const& objects, LightContainer const& lights) {
  return {objects, lights};
}

}

#endif
