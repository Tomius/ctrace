#ifndef PIXEL_ARRAY_100_HPP_
#define PIXEL_ARRAY_100_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray100<N> defines an N element array of pixels. N must be 100x + 1.
template<int N>
struct PixelArray100 {
  PixelArray100<N-100> contained;
  vec3 pixels[100];

  #define INIT(START_NUM) \
     colorOfPixel(N-100+10*START_NUM+0), colorOfPixel(N-100+10*START_NUM+1) \
    ,colorOfPixel(N-100+10*START_NUM+2), colorOfPixel(N-100+10*START_NUM+3) \
    ,colorOfPixel(N-100+10*START_NUM+4), colorOfPixel(N-100+10*START_NUM+5) \
    ,colorOfPixel(N-100+10*START_NUM+6), colorOfPixel(N-100+10*START_NUM+7) \
    ,colorOfPixel(N-100+10*START_NUM+8), colorOfPixel(N-100+10*START_NUM+9)

  constexpr PixelArray100()
      : pixels{INIT(0), INIT(1), INIT(2), INIT(3), INIT(4),
               INIT(5), INIT(6), INIT(7), INIT(8), INIT(9)} {
    static_assert((N-1) % 100 == 0, "N must be 100x + 1");
  }
};

template<>
struct PixelArray100<1> {
  vec3 pixel;
  constexpr PixelArray100() : pixel{colorOfPixel(0)} {}
};

using Screen = PixelArray100<kScreenWidth*kScreenHeight+1>;

}

#endif
