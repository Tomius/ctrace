#ifndef SCREEN_PIXEL_ARRAY_HPP_
#define SCREEN_PIXEL_ARRAY_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray<N> defines an N element array of pixels.
template<int N, typename Enable = void>
class PixelArray;

template<>
class PixelArray<1, void> {
  Color pixel;

 public:
  constexpr PixelArray() : pixel{colorOfPixel(0)} {}
};


}

#endif
