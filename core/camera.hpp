#ifndef CORE_CAMERA_HPP_
#define CORE_CAMERA_HPP_

#include "./scene.hpp"
#include "../scene_settings.hpp"

namespace ctrace {

class Camera {
 public:
  constexpr Camera(real fov, Vector const& eye,
                   Vector const& target, Vector const& plane_up)
      : pos(eye), plane_pos(eye + normalize(target-eye)) {
    Vector fwd = normalize(plane_pos - pos);
    real plane_half_size = tan((fov*M_PI/180)/2);

    right = plane_half_size * normalize(cross(fwd, plane_up));
    up = plane_half_size * normalize(cross(right, fwd));
  }

  template<typename Scene>
  constexpr Color capturePixel(real x, real y, Scene const& scene) const {
    Vector pos_on_plane = Vector{
      (x - kScreenWidth/2) / (kScreenWidth/2),
      (kScreenHeight/2 - y) / (kScreenHeight/2),
      0
    };

    Vector plane_intersection =
        plane_pos + pos_on_plane.x*right + pos_on_plane.y*up;

    Ray r = {pos, normalize(plane_intersection - pos)};
    return scene.shootRay(r);
  }

 private:
  Vector pos, plane_pos, right, up;
};

}

#endif
