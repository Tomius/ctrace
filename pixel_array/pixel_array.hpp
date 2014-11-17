#ifndef PIXEL_ARRAY_HPP_
#define PIXEL_ARRAY_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray<N> defines an N element array of pixels.
template<int N>
struct PixelArray {
  PixelArray<N-1> contained;
  vec3 pixel;
  constexpr PixelArray() : pixel{colorOfPixel(N-1)} { }
};

template<>
struct PixelArray<1> {
  vec3 pixel;
  constexpr PixelArray() : pixel{colorOfPixel(0)} {}
};

using Screen = PixelArray<kScreenWidth*kScreenHeight>;

}

#endif
