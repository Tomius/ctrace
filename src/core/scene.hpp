#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "./types.hpp"
#include "./camera.hpp"

namespace ctrace {

template <typename ObjectContainer, typename LightContainer>
class Scene {
 public:
  constexpr Scene(ObjectContainer const& objects,
                  LightContainer const& lights,
                  Camera const& camera)
    : objects_(objects), lights_(lights), camera_(camera) {}

  constexpr Color shootRay(Ray const& ray) const {
    return toneMap(objects_.intersectRay(ray, lights_));
  }

  constexpr Color colorOfPixel(int x, int y) const {
    return camera_.capturePixel(x, y, *this);
  }

  constexpr ObjectContainer const& objects() const { return objects_; }
  constexpr LightContainer const& lights() const { return lights_; }
  constexpr Camera const& camera() const { return camera_; }

 private:
  const ObjectContainer objects_;
  const LightContainer lights_;
  const Camera camera_;
};

template <typename ObjectContainer, typename LightContainer>
constexpr Scene<ObjectContainer, LightContainer>
makeScene(ObjectContainer const& objects,
          LightContainer const& lights,
          Camera const& camera) {
  return {objects, lights, camera};
}

}

#endif
