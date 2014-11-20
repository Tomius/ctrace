#ifndef CORE_RENDERER_HPP_
#define CORE_RENDERER_HPP_

#include "../scene_setup.hpp"

namespace ctrace {

constexpr Color colorOfPixel(int n) {
  return camera.capturePixel(n % kScreenWidth, n / kScreenWidth, scene);
}

}


#endif
