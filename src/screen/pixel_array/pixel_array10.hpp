#ifndef SCREEN_PIXEL_ARRAY_10_HPP_
#define SCREEN_PIXEL_ARRAY_10_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N, int S>
class PixelArray<N, S, std::enable_if_t<10 < N && N <= 100>> {
  PixelArray<N-10, S> contained_;
  Color pixels_[10];

 public:
  constexpr PixelArray()
      : pixels_{colorOfPixel(S+N-10), colorOfPixel(S+N-9),
                colorOfPixel(S+N-8),  colorOfPixel(S+N-7),
                colorOfPixel(S+N-6),  colorOfPixel(S+N-5),
                colorOfPixel(S+N-4),  colorOfPixel(S+N-3),
                colorOfPixel(S+N-2),  colorOfPixel(S+N-1)} { }
};

}

#endif
