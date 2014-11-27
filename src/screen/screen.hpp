#ifndef SCREEN_SCREEN_HPP_
#define SCREEN_SCREEN_HPP_

#include "./pixel_array.hpp"

namespace ctrace {

// Returns the number of the first pixel in the given image part.
constexpr unsigned startPixel(unsigned part, unsigned num_parts) {
  return kScreenWidth*(part*kScreenHeight/num_parts);
}

// Returns the number of pixels the partth segment of the screen containts.
// If you ask to separate a 5*10 image into 4 parts,
// then they will have sizes of 5*2, 5*3, 5*2, 5*3 respectively.
constexpr unsigned pixelCount(unsigned part, unsigned num_parts) {
  return startPixel(part+1, num_parts) - startPixel(part, num_parts);
}

// If you ask to separate a 5*10 image into 4 parts,
// then they will have sizes of 5*2, 5*3, 5*2, 5*3 respectively.
// That's the reason behind the tricky integer divison.
template<unsigned PART, unsigned NUM_PARTS>
struct Screen : private PixelArray<pixelCount(PART, NUM_PARTS)> {
  constexpr Screen()
    : PixelArray<pixelCount(PART, NUM_PARTS)>{startPixel(PART, NUM_PARTS)} {}

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
