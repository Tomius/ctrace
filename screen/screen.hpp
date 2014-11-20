#ifndef SCREEN_SCREEN_HPP_
#define SCREEN_SCREEN_HPP_

#include "./pixel_array.hpp"
#include "./pixel_array1.hpp"
#include "./pixel_array10.hpp"
#include "./pixel_array100.hpp"
#include "./pixel_array1000.hpp"

namespace ctrace {

// the number of pixels is usually a multiply of 1000
// 1001 can be turned into 2 array (1*1000 + terminator),
// while 1000 needs 28 template (9*100 + 9*10 + 9*1 + terminator),
// so overall using an array of 1001 is much faster than 1000
struct Screen : private PixelArray<kScreenWidth*kScreenHeight+1> {
  constexpr Screen() {}
  Color const* pixels() const {
    return reinterpret_cast<Color const*>(this);
  }
};

}

#endif
