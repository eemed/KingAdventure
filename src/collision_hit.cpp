#include "collision_hit.h"

namespace sdl_platformer
{
   CollisionHit::CollisionHit()
      : m_left(false), m_right(false),
        m_top(false), m_bottom(false),
        m_crush(false)
   {
   }

   CollisionHit::~CollisionHit()
   {
   }
}// sdl_platformer
