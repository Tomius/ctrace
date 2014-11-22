#ifndef SCENE_SETUP_HPP_
#define SCENE_SETUP_HPP_

#include "core/scene.hpp"
#include "core/camera.hpp"
#include "materials/diffuse_material.hpp"
#include "objects/triangle.hpp"
#include "objects/quad.hpp"
#include "objects/cuboid.hpp"
#include "objects/sphere.hpp"
#include "objects/object_container.hpp"
#include "lights/light_container.hpp"

namespace ctrace {

constexpr DiffuseMaterial red{Color{0, 0, 1}}; // :D
constexpr DiffuseMaterial yellow{Color{0.9, 0.8, 0.1}};
constexpr DiffuseMaterial grey{Color{0.3}};

constexpr auto scene = makeScene(
makeObjectContainer(
  // the blue sphere
  makeSphere(red, Vector{-2.5, +0.75, +2.5}, 1.5),

  // the yellow cube
  makeCuboid(yellow, Vector{+1, +1, -1}, Vector{+1, +1, +1},
                     Vector{+1, -1, -1}, Vector{-1, +1, -1}),

  // floor
  makeQuad(grey, Vector{-10, -1, -10}, Vector{-10, -1, +10},
                 Vector{+10, -1, +10}, Vector{+10, -1, -10})
),
makeLightContainer(
  AmbientLight{Color{0.1, 0.1, 0.1}},
  DirectionalLight{Vector{+1.2, 1, -0.8}, Color{0.25, 0.25, 0.25}},
  PointLight{Vector{-1.5, 2, 0}, Color{5, 4, 3}}
)
);

constexpr Camera camera{60, Vector{-4.5, 2.5, -3.5},
                        Vector{-1.25, 0, 1.25}, Vector{0, 1, 0}};

}

#endif
