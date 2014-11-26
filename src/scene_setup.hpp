#ifndef SCENE_SETUP_HPP_
#define SCENE_SETUP_HPP_

#include "core/scene.hpp"
#include "objects/objects.hpp"
#include "lights/light_container.hpp"
#include "materials/diffuse_material.hpp"

namespace ctrace {

constexpr auto blue = makeDiffuseMaterial(SimpleColorMapper{Color{0, 0, 1}});
constexpr auto yellow = makeDiffuseMaterial(SimpleColorMapper{Color{0.9, 0.8, 0.1}});
constexpr auto normal_material = makeDiffuseMaterial(NormalVectorColorMapper<2>{});

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
