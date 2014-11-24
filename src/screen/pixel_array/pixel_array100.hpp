#ifndef SCREEN_PIXEL_ARRAY_100_HPP_
#define SCREEN_PIXEL_ARRAY_100_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N, int S>
class PixelArray<N, S, std::enable_if_t<100 < N && N <= 1000>> {
  PixelArray<N-100, S> contained_;
  Color pixels_[100];

  #define __INIT(START_NUM) \
     colorOfPixel(S+N-100+10*START_NUM+0), colorOfPixel(S+N-100+10*START_NUM+1) \
    ,colorOfPixel(S+N-100+10*START_NUM+2), colorOfPixel(S+N-100+10*START_NUM+3) \
    ,colorOfPixel(S+N-100+10*START_NUM+4), colorOfPixel(S+N-100+10*START_NUM+5) \
    ,colorOfPixel(S+N-100+10*START_NUM+6), colorOfPixel(S+N-100+10*START_NUM+7) \
    ,colorOfPixel(S+N-100+10*START_NUM+8), colorOfPixel(S+N-100+10*START_NUM+9)

 public:
  constexpr PixelArray()
      : pixels_{__INIT(0), __INIT(1), __INIT(2), __INIT(3), __INIT(4),
                __INIT(5), __INIT(6), __INIT(7), __INIT(8), __INIT(9)} {}

  #undef __INIT
};

}

#endif
