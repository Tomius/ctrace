#ifndef SCREEN_PIXEL_ARRAY_HPP_
#define SCREEN_PIXEL_ARRAY_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray<N> defines an N element "array" of pixels.
// reinterpret_cast<Color const*>(PixelArray<N>*) can be
// used just as static_cast<Color const*>(Color const[N])
template<unsigned N>
class PixelArray {
  // Notice how the template recursion depth scales with only log2(N).
  const PixelArray<N/2> sub_array0_;
  const PixelArray<N-N/2> sub_array1_;

 public:
  constexpr PixelArray(unsigned start_pixel_num)
      : sub_array0_{start_pixel_num}, sub_array1_{start_pixel_num + N/2} { }
};

template<>
class PixelArray<1> {
  const Color pixel_;

 public:
  constexpr PixelArray(unsigned pixel_num) : pixel_{colorOfPixel(pixel_num)} {}
};

}

#endif
