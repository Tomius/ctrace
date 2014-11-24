#ifndef SCREEN_PIXEL_ARRAY_HPP_
#define SCREEN_PIXEL_ARRAY_HPP_

#include "../../core/renderer.hpp"

namespace ctrace {

// PixelArray<N> defines an N element array of pixels.
// S defines the number of the starting pixel in the array.
template<int N, int S, typename Enable = void>
class PixelArray;

}

#include "./pixel_array1.hpp"
#include "./pixel_array10.hpp"
#include "./pixel_array100.hpp"
#include "./pixel_array1000.hpp"

#endif
