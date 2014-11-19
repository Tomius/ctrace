#ifndef LIGHTS_HPP_
#define LIGHTS_HPP_

namespace ctrace {

struct Light { constexpr Light() {} };

struct AmbientLight : Light{
  Color color;
  constexpr AmbientLight(Color const& color) : color(color) {}
};

struct DirectionalLight : Light {
  Vector dir;
  Color color;
  constexpr DirectionalLight(Vector const& dir, Color const& color)
      : dir(dir), color(color) {}
};

struct PointLight : Light {
  Vector pos;
  Color color;
  constexpr PointLight(Vector const& pos, Color const& color)
      : pos(pos), color(color) {}
};

}

#endif