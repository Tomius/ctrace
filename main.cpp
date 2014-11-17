#include <Magick++.h>
#include "pixel_array/pixel_array1000.hpp"

using namespace ctrace;

int main(int argc,char **argv) {
  constexpr Screen screen;
  const vec3 *pixels = reinterpret_cast<const vec3*>(&screen);

  Magick::InitializeMagick(*argv);
  Magick::Image image{kScreenWidth, kScreenHeight, "RGB",
                Magick::StorageType::FloatPixel, pixels};
  image.write("out.png");
}


