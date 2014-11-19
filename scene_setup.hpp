#ifndef SCENE_SETUP_HPP_
#define SCENE_SETUP_HPP_

#include "core/scene.hpp"
#include "core/camera.hpp"
#include "materials/diffuse_material.hpp"
#include "objects/triangle.hpp"
#include "objects/object_container.hpp"
#include "lights/light_container.hpp"

namespace ctrace {

constexpr DiffuseMaterial yellow{Color{0.9f, 0.8f, 0.1f}};
constexpr DiffuseMaterial grey{Color{0.3f}};

constexpr auto scene = makeScene(
makeObjectContainer(
  // cube front face
  makeTriangle(yellow, Vector{+1, -1, -1}, Vector{-1, -1, -1}, Vector{-1, +1, -1}),
  makeTriangle(yellow, Vector{-1, +1, -1}, Vector{+1, +1, -1}, Vector{+1, -1, -1}),

  // cube back face
  makeTriangle(yellow, Vector{+1, -1, +1}, Vector{-1, -1, +1}, Vector{-1, +1, +1}),
  makeTriangle(yellow, Vector{-1, +1, +1}, Vector{+1, +1, +1}, Vector{+1, -1, +1}),

  // cube right face
  makeTriangle(yellow, Vector{+1, -1, -1}, Vector{+1, -1, +1}, Vector{+1, +1, +1}),
  makeTriangle(yellow, Vector{+1, +1, +1}, Vector{+1, +1, -1}, Vector{+1, -1, -1}),

  // cube left face
  makeTriangle(yellow, Vector{-1, +1, +1}, Vector{-1, +1, -1}, Vector{-1, -1, -1}),
  makeTriangle(yellow, Vector{-1, -1, -1}, Vector{-1, -1, +1}, Vector{-1, +1, +1}),

  // cube upper face
  makeTriangle(yellow, Vector{-1, +1, -1}, Vector{-1, +1, +1}, Vector{+1, +1, +1}),
  makeTriangle(yellow, Vector{+1, +1, -1}, Vector{-1, +1, -1}, Vector{+1, +1, +1}),

  // cube lower face
  makeTriangle(yellow, Vector{-1, -1, +1}, Vector{-1, -1, -1}, Vector{+1, -1, +1}),
  makeTriangle(yellow, Vector{+1, -1, -1}, Vector{+1, -1, +1}, Vector{-1, -1, -1}),

  // floor
  makeTriangle(grey, Vector{-10, -1, -10}, Vector{-10, -1, +10}, Vector{+10, -1, +10}),
  makeTriangle(grey, Vector{+10, -1, -10}, Vector{-10, -1, -10}, Vector{+10, -1, +10})
),
makeLightContainer(
  AmbientLight{Color{0.1f, 0.1f, 0.1f}},
  DirectionalLight{Vector{-1.2, 1, -0.8}, Color{0.8f, 0.8f, 0.8f}},
  PointLight{Vector{-1.5, 2, 0}, Color{10, 8, 7}}
)
);

constexpr Camera camera{60, Vector(-3, 2.5, -2), Vector(), Vector(0, 1, 0)};

}

#endif
