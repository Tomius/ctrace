#ifndef NORMAL_VECTOR_COLOR_MAPPER_HPP_
#define NORMAL_VECTOR_COLOR_MAPPER_HPP_

#include "../math/vec3.hpp"

namespace ctrace {

template<unsigned TYPE>
class NormalVectorColorMapper {
 public:
  constexpr Color ambientColor(Intersection const& intersection) const {
    return color(intersection);
  }
  constexpr Color diffuseColor(Intersection const& intersection) const {
    return color(intersection);
  }

 private:
  constexpr Color color(Intersection const& intersection) const {
    static_assert(TYPE <= 2, "");
    switch(TYPE) {
      case 0: {
        Direction n = intersection.normal;
        return Color(abs(n.x), abs(n.y), abs(n.z));
      } case 1: {
        return (intersection.normal+1)/2;
      } case 2: {
        return (1-intersection.normal)/2;
      }
    }
  }
};

}

#endif
