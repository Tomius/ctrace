#ifndef SCENE_SETUP_HPP_
#define SCENE_SETUP_HPP_

#include "core/scene.hpp"
#include "objects/objects.hpp"
#include "lights/light_container.hpp"
#include "materials/diffuse_material.hpp"

namespace ctrace {

constexpr auto blue = makeDiffuseMaterial(SimpleColorMapper{Color{0, 0, 1}});
constexpr auto yellow = makeDiffuseMaterial(SimpleColorMapper{Color{0.9, 0.8, 0.1}});
constexpr auto normal1 = makeDiffuseMaterial(NormalVectorColorMapper<1>{});
constexpr auto normal2 = makeDiffuseMaterial(NormalVectorColorMapper<2>{});

constexpr auto scene = makeScene(
  makeObjectContainer(
    // blue sphere
    makeSphere(blue, Position{-1, +1.35, +1}, 1.35),

    // the containing cube
    makeAxisAlignedCuboid(normal1, Position{0, 7.5, 0}, Vector{15}),

    // the small yellow cube
    makeAxisAlignedCuboid(yellow, Position{+1, 0.75, -1}, Vector{1.5}),

    // the floating mult-color spehere
    makeSphere(normal2, Position{2, 3.7, 2}, 1.5)
  ),

  makeLightContainer(
    AmbientLight{Color{0.2, 0.2, 0.2}},
    PointLight{Position{-1.5, 4, 0}, Color{5, 4, 3}},
    PointLight{Position{-2, 2, -2}, Color{2, 4, 6}}
  ),

  Camera{
    60, // field of view
    Position{-4, 3, -4}, // eye pos
    Position{0, 2, 0}, // look target (whats in the center of the image)
    Direction{0, 1, 0} // what's up?
  }
);

}

#endif
