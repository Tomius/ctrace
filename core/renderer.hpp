#ifndef CORE_RENDERER_HPP_
#define CORE_RENDERER_HPP_

#include "../scene_setup.hpp"

namespace ctrace {

constexpr vec3 colorOfPixel(int x, int y) {
  return camera.capturePixel(x, y, scene);
}

constexpr vec3 colorOfPixel(int n) {
  return colorOfPixel(n % kScreenWidth, n / kScreenWidth);
}

}


#endif
