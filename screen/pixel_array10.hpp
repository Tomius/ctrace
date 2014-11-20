#ifndef SCREEN_PIXEL_ARRAY_10_HPP_
#define SCREEN_PIXEL_ARRAY_10_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N>
class PixelArray<N, std::enable_if_t<10 < N && N <= 100>> {
  PixelArray<N-10> contained;
  Color pixels[10];

 public:
  constexpr PixelArray()
      : pixels{colorOfPixel(N-10), colorOfPixel(N-9),
               colorOfPixel(N-8), colorOfPixel(N-7),
               colorOfPixel(N-6), colorOfPixel(N-5),
               colorOfPixel(N-4), colorOfPixel(N-3),
               colorOfPixel(N-2), colorOfPixel(N-1)} { }
};

}

#endif
