#ifndef SCREEN_PIXEL_ARRAY_HPP_
#define SCREEN_PIXEL_ARRAY_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray<N> defines an N element array of pixels.
template<int N, typename Enable = void>
struct PixelArray;

template<>
struct PixelArray<1, void> {
  Color pixel;
  constexpr PixelArray() : pixel{colorOfPixel(0)} {}
};


}

#endif
