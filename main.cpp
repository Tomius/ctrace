#include <memory>
#include <iostream>
#include <Magick++.h>
#include "screen/screen.hpp"

using namespace ctrace;

int main(int argc,char **argv) {
  constexpr Screen screen;

  Magick::InitializeMagick(*argv);
  Magick::Image image{kScreenWidth, kScreenHeight, "RGB",
                      Magick::StorageType::FloatPixel, screen.pixels()};
  image.write("out.png");
}
