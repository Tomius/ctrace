#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "./types.hpp"

namespace ctrace {

template <typename ObjectContainer, typename LightContainer>
class Scene {
 public:
  constexpr Scene(ObjectContainer const& objects,
                  LightContainer const& lights)
    : objects_(objects), lights_(lights) {}

  constexpr Color shootRay(Ray const& ray) const {
    return toneMap(objects_.intersectRay(ray, lights_));
  }

 private:
  ObjectContainer objects_;
  LightContainer lights_;
};

template <typename ObjectContainer, typename LightContainer>
constexpr Scene<ObjectContainer, LightContainer>
makeScene(ObjectContainer const& objects, LightContainer const& lights) {
  return {objects, lights};
}

}

#endif
