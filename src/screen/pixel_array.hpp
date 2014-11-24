#ifndef SCREEN_PIXEL_ARRAY_HPP_
#define SCREEN_PIXEL_ARRAY_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray<N> defines an N element array of pixels.
// S defines the number of the starting pixel in the array.
template<int N, int S>
class PixelArray {
  // Notice how the template recursion depth scales with only log2(N).
  // So basically you can make arrays of up to 10^77 elements, without
  // having to change -ftemplate-depth
  PixelArray<N/2, S> sub_array0_;
  PixelArray<N-N/2, S+N/2> sub_array1_;

 public:
  constexpr PixelArray() { }
};

template<int S>
class PixelArray<1, S> {
  Color pixel_;
 public:
  constexpr PixelArray() : pixel_{colorOfPixel(S)} {}
};

}

#endif
