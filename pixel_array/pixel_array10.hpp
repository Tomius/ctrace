#ifndef PIXEL_ARRAY_10_HPP_
#define PIXEL_ARRAY_10_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray10<N> defines an N element array of pixels. N must be 10x + 1.
template<int N>
struct PixelArray10 {
  PixelArray10<N-10> contained;
  vec3 pixels[10];
  constexpr PixelArray10()
      : pixels{colorOfPixel(N-10), colorOfPixel(N-9),
               colorOfPixel(N-8), colorOfPixel(N-7),
               colorOfPixel(N-6), colorOfPixel(N-5),
               colorOfPixel(N-4), colorOfPixel(N-3),
               colorOfPixel(N-2), colorOfPixel(N-1)} {
    static_assert((N-1) % 10 == 0, "N must be 10x + 1");
  }
};

template<>
struct PixelArray10<1> {
  vec3 pixel;
  constexpr PixelArray10() : pixel{colorOfPixel(0)} {}
};

using Screen = PixelArray10<kScreenWidth*kScreenHeight+1>;

}

#endif
