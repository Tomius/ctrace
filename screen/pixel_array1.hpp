#ifndef SCREEN_PIXEL_ARRAY1_HPP_
#define SCREEN_PIXEL_ARRAY1_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

template<int N>
struct PixelArray<N, std::enable_if_t<1 < N && N <= 10>> {
  PixelArray<N-1> contained;
  Color pixel;
  constexpr PixelArray() : pixel{colorOfPixel(N-1)} { }
};

}

#endif
