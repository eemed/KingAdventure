#include "collision_vector.h"

namespace sdl_platformer
{

   bool
   determine_hit(int x, int y)
   {
      return !(x == 0 and y == 0);
   }

   CollisionVector::CollisionVector(int x, int y, CollisionHit hit_info)
      : Vector(x, y),
      m_hit( determine_hit(x, y) ),
      m_collision_info(hit_info)
   {
   }

   CollisionVector::~CollisionVector()
   {
   }
}// namespace sdl_platformer
