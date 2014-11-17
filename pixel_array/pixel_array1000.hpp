#ifndef PIXEL_ARRAY_1000_HPP_
#define PIXEL_ARRAY_1000_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray1000<N> defines an N element array of pixels. N must be 1000x + 1.
template<int N>
struct PixelArray1000 {
  PixelArray1000<N-1000> contained;
  vec3 pixels[1000];

  #define INIT(START_NUM) \
     colorOfPixel(N-1000+25*START_NUM+ 0), colorOfPixel(N-1000+25*START_NUM+ 1) \
    ,colorOfPixel(N-1000+25*START_NUM+ 2), colorOfPixel(N-1000+25*START_NUM+ 3) \
    ,colorOfPixel(N-1000+25*START_NUM+ 4), colorOfPixel(N-1000+25*START_NUM+ 5) \
    ,colorOfPixel(N-1000+25*START_NUM+ 6), colorOfPixel(N-1000+25*START_NUM+ 7) \
    ,colorOfPixel(N-1000+25*START_NUM+ 8), colorOfPixel(N-1000+25*START_NUM+ 9) \
    ,colorOfPixel(N-1000+25*START_NUM+10), colorOfPixel(N-1000+25*START_NUM+11) \
    ,colorOfPixel(N-1000+25*START_NUM+12), colorOfPixel(N-1000+25*START_NUM+13) \
    ,colorOfPixel(N-1000+25*START_NUM+14), colorOfPixel(N-1000+25*START_NUM+15) \
    ,colorOfPixel(N-1000+25*START_NUM+16), colorOfPixel(N-1000+25*START_NUM+17) \
    ,colorOfPixel(N-1000+25*START_NUM+18), colorOfPixel(N-1000+25*START_NUM+19) \
    ,colorOfPixel(N-1000+25*START_NUM+20), colorOfPixel(N-1000+25*START_NUM+21) \
    ,colorOfPixel(N-1000+25*START_NUM+22), colorOfPixel(N-1000+25*START_NUM+23) \
    ,colorOfPixel(N-1000+25*START_NUM+24)

  constexpr PixelArray1000()
      : pixels{INIT( 0), INIT( 1), INIT( 2), INIT( 3), INIT( 4) , INIT( 5), INIT( 6), INIT( 7), INIT( 8), INIT( 9),
               INIT(10), INIT(11), INIT(12), INIT(13), INIT(14) , INIT(15), INIT(16), INIT(17), INIT(18), INIT(19),
               INIT(20), INIT(21), INIT(22), INIT(23), INIT(24) , INIT(25), INIT(26), INIT(27), INIT(28), INIT(29),
               INIT(30), INIT(31), INIT(32), INIT(33), INIT(34) , INIT(35), INIT(36), INIT(37), INIT(38), INIT(39)} {
    static_assert((N-1) % 1000 == 0, "N must be 1000x + 1");
  }
};

template<>
struct PixelArray1000<1> {
  vec3 pixel;
  constexpr PixelArray1000() : pixel{colorOfPixel(0)} {}
};

using Screen = PixelArray1000<kScreenWidth*kScreenHeight+1>;

}

#endif
