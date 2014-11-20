#ifndef SCREEN_PIXEL_ARRAY_100_HPP_
#define SCREEN_PIXEL_ARRAY_100_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N>
class PixelArray<N, std::enable_if_t<100 < N && N <= 1000>> {
  PixelArray<N-100> contained;
  Color pixels[100];

  #define __INIT(START_NUM) \
     colorOfPixel(N-100+10*START_NUM+0), colorOfPixel(N-100+10*START_NUM+1) \
    ,colorOfPixel(N-100+10*START_NUM+2), colorOfPixel(N-100+10*START_NUM+3) \
    ,colorOfPixel(N-100+10*START_NUM+4), colorOfPixel(N-100+10*START_NUM+5) \
    ,colorOfPixel(N-100+10*START_NUM+6), colorOfPixel(N-100+10*START_NUM+7) \
    ,colorOfPixel(N-100+10*START_NUM+8), colorOfPixel(N-100+10*START_NUM+9)

 public:
  constexpr PixelArray()
      : pixels{__INIT(0), __INIT(1), __INIT(2), __INIT(3), __INIT(4),
               __INIT(5), __INIT(6), __INIT(7), __INIT(8), __INIT(9)} {}

  #undef __INIT
};

}

#endif
