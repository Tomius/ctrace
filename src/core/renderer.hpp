#ifndef CORE_RENDERER_HPP_
#define CORE_RENDERER_HPP_

#include "../scene_setup.hpp"

namespace ctrace {

constexpr Color colorOfPixel(int n) {
  return scene.colorOfPixel(n % kScreenWidth, n / kScreenWidth);
}

// the scene global variable was not available when this function was
// declared, so I just define it here - right after scene got defined.
constexpr Intersection intersectRay(Ray const& ray) {
  return scene.objects().intersectRay(ray);
}

}


#endif
