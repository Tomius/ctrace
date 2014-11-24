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
  using namespace Magick;
  using namespace ctrace;

  InitializeMagick(*argv);

  // we have to merge the image parts.
  StorageType storage_type = GetStorageType();
  Image image0{kScreenWidth, kScreenHeight/4, "RGB", storage_type, screen_part_0.pixels()};
  Image image1{kScreenWidth, kScreenHeight/4, "RGB", storage_type, screen_part_1.pixels()};
  Image image2{kScreenWidth, kScreenHeight/4, "RGB", storage_type, screen_part_2.pixels()};
  Image image3{kScreenWidth, kScreenHeight/4, "RGB", storage_type, screen_part_3.pixels()};

  Image image{Geometry{kScreenWidth, kScreenHeight}, ColorRGB{}};
  image.composite(image0, 0, 0*kScreenHeight/4, CopyCompositeOp);
  image.composite(image1, 0, 1*kScreenHeight/4, CopyCompositeOp);
  image.composite(image2, 0, 2*kScreenHeight/4, CopyCompositeOp);
  image.composite(image3, 0, 3*kScreenHeight/4, CopyCompositeOp);
  image.write("out.png");
}
