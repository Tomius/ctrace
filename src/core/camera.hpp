#ifndef CORE_CAMERA_HPP_
#define CORE_CAMERA_HPP_

#include "../scene_settings.hpp"

namespace ctrace {

class Camera {
 public:
  constexpr Camera(real fov, Position const& eye,
                   Position const& target, Direction const& up)
      : eye_pos_(eye), plane_pos_(eye + normalize(target-eye)) {
    Direction fwd = normalize(plane_pos_ - eye_pos_);
    real plane_half_size = tan((fov*M_PI/180)/2);

    // the length of the up and the right
    // vectors are storing the field of view too
    right_ = plane_half_size * normalize(cross(fwd, up));
    up_ = plane_half_size * normalize(cross(right_, fwd));
  }

  template<typename Scene>
  constexpr Color capturePixel(real x, real y, Scene const& scene) const {
    Position pos_on_plane = Position{
      (x - kScreenWidth/2) / (kScreenWidth/2),
      (kScreenHeight/2 - y) / (kScreenHeight/2),
      0
    };

    Position plane_intersection =
        plane_pos_ + pos_on_plane.x*right_ + pos_on_plane.y*up_;

    Ray r = {eye_pos_, normalize(plane_intersection - eye_pos_)};
    return scene.shootRay(r);
  }

 private:
  Position eye_pos_, plane_pos_;
  Direction right_, up_;
};

}

#endif
