#ifndef SCREEN_SCREEN_HPP_
#define SCREEN_SCREEN_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

// the number of pixels is usually a multiply of 1000.
// A 1001 elem array can created using 2 templates (1*1000 + terminator),
// while a 1000 elem array needs 28 templates (9*100 + 9*10 + 9*1 + terminator),
// so overall using an array of 1001 elems is much faster than 1000,
// so it might worth it to add one to the size of the pixel array,
// even though that pixel is never actually used.
struct Screen : private PixelArray<kScreenWidth*kScreenHeight+1> {
  constexpr Screen() {}
  Color const* pixels() const { // reinterpret_cast can't be constexpr
    return reinterpret_cast<Color const*>(this);
  }
};

}

#endif
