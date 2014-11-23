#ifndef SCREEN_PIXEL_ARRAY1_HPP_
#define SCREEN_PIXEL_ARRAY1_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N>
class PixelArray<N, std::enable_if_t<1 < N && N <= 10>> {
  PixelArray<N-1> contained_;
  Color pixel_;

 public:
  constexpr PixelArray() : pixel_{colorOfPixel(N-1)} { }
};

template<>
class PixelArray<1, void> {
  Color pixel_;

 public:
  constexpr PixelArray() : pixel_{colorOfPixel(0)} {}
};

}

#endif
