#ifndef CORE_RENDERER_HPP_
#define CORE_RENDERER_HPP_

#include "../scene_setup.hpp"

namespace ctrace {

constexpr Color colorOfPixel(int x, int y) {
  return camera.capturePixel(x, y, scene);
}

constexpr Color colorOfPixel(int n) {
  return colorOfPixel(n % kScreenWidth, n / kScreenWidth);
}

}


#endif
