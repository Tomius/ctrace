#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "./types.hpp"

namespace ctrace {

template <typename Objects>
struct Scene {
  Objects objects;
  constexpr Scene(Objects objects) : objects(objects) {}

  constexpr vec3 shootRay(Ray const& ray) const {
    return objects.intersectRay(ray, Fragment{}).color;
  }
};

}

#endif
