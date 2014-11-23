#ifndef SCREEN_PIXEL_ARRAY_1000_HPP_
#define SCREEN_PIXEL_ARRAY_1000_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N>
class PixelArray<N, std::enable_if_t<1000 < N>> {
  PixelArray<N-1000> contained_;
  Color pixels_[1000];

  #define __INIT(START_NUM) \
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

public:
  constexpr PixelArray()
      : pixels_{__INIT( 0), __INIT( 1), __INIT( 2), __INIT( 3), __INIT( 4),
                __INIT( 5), __INIT( 6), __INIT( 7), __INIT( 8), __INIT( 9),
                __INIT(10), __INIT(11), __INIT(12), __INIT(13), __INIT(14),
                __INIT(15), __INIT(16), __INIT(17), __INIT(18), __INIT(19),
                __INIT(20), __INIT(21), __INIT(22), __INIT(23), __INIT(24),
                __INIT(25), __INIT(26), __INIT(27), __INIT(28), __INIT(29),
                __INIT(30), __INIT(31), __INIT(32), __INIT(33), __INIT(34),
                __INIT(35), __INIT(36), __INIT(37), __INIT(38), __INIT(39)} {}

  #undef __INIT
};

}

#endif
