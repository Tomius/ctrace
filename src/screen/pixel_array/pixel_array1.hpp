#ifndef SCREEN_PIXEL_ARRAY1_HPP_
#define SCREEN_PIXEL_ARRAY1_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N, int S>
class PixelArray<N, S, std::enable_if_t<1 < N && N <= 10>> {
  PixelArray<N-1, S> contained_;
  Color pixel_;

 public:
  constexpr PixelArray() : pixel_{colorOfPixel(S+N-1)} { }
};

template<int S>
class PixelArray<1, S, void> {
  Color pixel_;

 public:
  constexpr PixelArray() : pixel_{colorOfPixel(S)} {}
};

}

#endif
