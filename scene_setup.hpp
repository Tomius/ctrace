#ifndef SCENE_SETUP_HPP_
#define SCENE_SETUP_HPP_

#include "core/scene.hpp"
#include "core/camera.hpp"
#include "materials/simple_material.hpp"
#include "objects/triangle.hpp"
#include "objects/objects.hpp"

namespace ctrace {

constexpr SimpleMaterial yellow{vec3{0.9, 0.8, 0}};

constexpr auto objects = makeObjects(
  // front face
  makeTriangle(yellow, vec3{+1, -1, -1}, vec3{-1, -1, -1}, vec3{-1, +1, -1}),
  makeTriangle(yellow, vec3{-1, +1, -1}, vec3{+1, +1, -1}, vec3{+1, -1, -1}),

  // back face
  makeTriangle(yellow, vec3{+1, -1, +1}, vec3{-1, -1, +1}, vec3{-1, +1, +1}),
  makeTriangle(yellow, vec3{-1, +1, +1}, vec3{+1, +1, +1}, vec3{+1, -1, +1}),

  // right face
  makeTriangle(yellow, vec3{+1, -1, -1}, vec3{+1, -1, +1}, vec3{+1, +1, +1}),
  makeTriangle(yellow, vec3{+1, +1, +1}, vec3{+1, +1, -1}, vec3{+1, -1, -1}),

  // left face
  makeTriangle(yellow, vec3{-1, +1, +1}, vec3{-1, +1, -1}, vec3{-1, -1, -1}),
  makeTriangle(yellow, vec3{-1, -1, -1}, vec3{-1, -1, +1}, vec3{-1, +1, +1}),

  // upper face
  makeTriangle(yellow, vec3{-1, +1, -1}, vec3{-1, +1, +1}, vec3{+1, +1, +1}),
  makeTriangle(yellow, vec3{+1, +1, -1}, vec3{-1, +1, -1}, vec3{+1, +1, +1}),

  // lower face
  makeTriangle(yellow, vec3{-1, -1, +1}, vec3{-1, -1, -1}, vec3{+1, -1, +1}),
  makeTriangle(yellow, vec3{+1, -1, -1}, vec3{+1, -1, +1}, vec3{-1, -1, -1})
);

constexpr Scene<decltype(objects)> scene{objects};

constexpr Camera camera{60, vec3(-3, 2, -2), vec3(), vec3(0, 1, 0)};
}

#endif
