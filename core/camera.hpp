#ifndef CORE_CAMERA_HPP_
#define CORE_CAMERA_HPP_

#include "./scene.hpp"

namespace ctrace {

constexpr unsigned kScreenWidth = 100;
constexpr unsigned kScreenHeight = 100;

struct Camera {
  vec3 pos, plane_pos, right, up;

  constexpr Camera(float fov, vec3 const& eye,
                   vec3 const& target, vec3 const& plane_up)
      : pos(eye), plane_pos(eye + normalize(target-eye)) {
    vec3 fwd = normalize(plane_pos - pos);
    float plane_half_size = tan((fov*M_PI/180)/2);

    right = plane_half_size * normalize(cross(fwd, plane_up));
    up = plane_half_size * normalize(cross(right, fwd));
  }

  template<typename T>
  constexpr vec3 capturePixel(float x, float y, Scene<T> const& scene) const {
    vec3 pos_on_plane = vec3{
      (x - kScreenWidth/2) / (kScreenWidth/2),
      (kScreenHeight/2 - y) / (kScreenHeight/2),
      0
    };

    vec3 plane_intersection =
        plane_pos + pos_on_plane.x*right + pos_on_plane.y*up;

    Ray r = {pos, normalize(plane_intersection - pos)};
    return scene.shootRay(r);
  }
};

}

#endif
