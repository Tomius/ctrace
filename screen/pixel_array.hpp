#ifndef SCREEN_PIXEL_ARRAY_HPP_
#define SCREEN_PIXEL_ARRAY_HPP_

#include "../core/renderer.hpp"

namespace ctrace {

// PixelArray<N> defines an N element array of pixels.
template<int N, typename Enable = void>
class PixelArray;

}

#include "./pixel_array1.hpp"
#include "./pixel_array10.hpp"
#include "./pixel_array100.hpp"
#include "./pixel_array1000.hpp"

#endif
