#include <Magick++.h>
#include "screen/screen.hpp"

static Magick::StorageType GetStorageType() {
  constexpr bool is_float = std::is_same<ctrace::real, float>::value;
  constexpr bool is_double = std::is_same<ctrace::real, double>::value;
  static_assert(is_float || is_double, "unrecognized pixel type");

  using Magick::StorageType;
  return is_float ? StorageType::FloatPixel : StorageType::DoublePixel;
}

int main(int argc, char **argv) {
  constexpr ctrace::Screen screen;

  Magick::InitializeMagick(*argv);
  Magick::Image image{ctrace::kScreenWidth, ctrace::kScreenHeight,
                      "RGB", GetStorageType(), screen.pixels()};
  image.write("out.png");
}
