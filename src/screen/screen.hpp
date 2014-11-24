#ifndef SCREEN_SCREEN_HPP_
#define SCREEN_SCREEN_HPP_

#include "pixel_array/pixel_array.hpp"

namespace ctrace {

// the number of pixels is usually a multiply of 1000.
// A 1001 elem array can created using 2 templates (1*1000 + terminator),
// while a 1000 elem array needs 28 templates (9*100 + 9*10 + 9*1 + terminator),
// so overall using an array of 1001 elems is much faster than 1000,
// so it might worth it to add one to the size of the pixel array,
// even though that pixel is never actually used.
template<int PART, int NUM_PARTS>
struct Screen : private PixelArray<kScreenWidth*kScreenHeight/NUM_PARTS+1,
                                   PART*kScreenWidth*kScreenHeight/NUM_PARTS> {
  constexpr Screen() {}
  Color const* pixels() const { // reinterpret_cast can't be constexpr
    return reinterpret_cast<Color const*>(this);
  }
};

extern const Screen<0, 4> screen_part_0;
extern const Screen<1, 4> screen_part_1;
extern const Screen<2, 4> screen_part_2;
extern const Screen<3, 4> screen_part_3;
static_assert(kScreenHeight%4==0, "The screen's height must be a multiple of 4");

}

#endif
