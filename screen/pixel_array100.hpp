#ifndef SCREEN_PIXEL_ARRAY_100_HPP_
#define SCREEN_PIXEL_ARRAY_100_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N>
struct PixelArray<N, std::enable_if_t<100 < N && N <= 1000>> {
  PixelArray<N-100> contained;
  Color pixels[100];

  #define INIT(START_NUM) \
     colorOfPixel(N-100+10*START_NUM+0), colorOfPixel(N-100+10*START_NUM+1) \
    ,colorOfPixel(N-100+10*START_NUM+2), colorOfPixel(N-100+10*START_NUM+3) \
    ,colorOfPixel(N-100+10*START_NUM+4), colorOfPixel(N-100+10*START_NUM+5) \
    ,colorOfPixel(N-100+10*START_NUM+6), colorOfPixel(N-100+10*START_NUM+7) \
    ,colorOfPixel(N-100+10*START_NUM+8), colorOfPixel(N-100+10*START_NUM+9)

  constexpr PixelArray()
      : pixels{INIT(0), INIT(1), INIT(2), INIT(3), INIT(4),
               INIT(5), INIT(6), INIT(7), INIT(8), INIT(9)} {}

  #undef INIT
};

}

#endif
