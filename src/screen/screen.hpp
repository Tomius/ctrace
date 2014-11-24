#ifndef SCREEN_SCREEN_HPP_
#define SCREEN_SCREEN_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

// If you ask to separate a 5*10 image into 4 parts,
// then they will have sizes of 5*2, 5*3, 5*2, 5*3 respectively.
// That's the reason behind the tricky integer divison.
template<int PART, int NUM_PARTS>
struct Screen : private PixelArray<
    kScreenWidth*((PART+1)*kScreenHeight/NUM_PARTS
                  - PART*kScreenHeight/NUM_PARTS),
    kScreenWidth*(PART*kScreenHeight/NUM_PARTS)> {
  constexpr Screen() {}
  Color const* pixels() const { // reinterpret_cast can't be constexpr
    return reinterpret_cast<Color const*>(this);
  }
};

extern template struct Screen<0, 4>;
extern template struct Screen<1, 4>;
extern template struct Screen<2, 4>;
extern template struct Screen<3, 4>;
extern const Screen<0, 4> screen_part_0;
extern const Screen<1, 4> screen_part_1;
extern const Screen<2, 4> screen_part_2;
extern const Screen<3, 4> screen_part_3;

}

#endif
