#ifndef SCENE_SETUP_HPP_
#define SCENE_SETUP_HPP_

#include "core/scene.hpp"
#include "core/camera.hpp"
#include "materials/diffuse_material.hpp"
#include "materials/normal2color_material.hpp"
#include "objects/triangle.hpp"
#include "objects/quad.hpp"
#include "objects/cuboid.hpp"
#include "objects/sphere.hpp"
#include "objects/object_container.hpp"
#include "lights/light_container.hpp"

namespace ctrace {

constexpr DiffuseMaterial blue{Color{0, 0, 1}};
constexpr DiffuseMaterial yellow{Color{0.9, 0.8, 0.1}};
constexpr Normal2ColorMaterial normal_material{};

constexpr auto scene = makeScene(
  makeObjectContainer(
    // blue sphere
    makeSphere(blue, Position{-2.5, +1.35, +2.5}, 1.35),

    // the containing cube
    makeAxisAlignedCuboid(normal_material, Position{0, 7.5, 0}, Vector{15}),

    // the small yellow cube
    makeAxisAlignedCuboid(yellow, Position{0, 0.75, 0}, Vector{1.5})
  ),

  makeLightContainer(
    AmbientLight{Color{0.1, 0.1, 0.1}},
    PointLight{Position{-1.5, 2, 0}, Color{5, 4, 3}}
  ),

  Camera{
    60, Position{-4.5, 2.5, -3.5}, Position{-1.25, 0, 1.25}, Direction{0, 1, 0}
  }
);

}

#endif
