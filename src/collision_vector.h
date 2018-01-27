#ifndef _COLLISION_VECTOR_
#define _COLLISION_VECTOR_

#include "vector.h"
#include "collision_hit.h"

namespace sdl_platformer
{
   class CollisionVector : public Vector
   {
      public:

         bool m_hit;
         CollisionHit m_collision_info;

         CollisionVector(int x = 0, int y = 0, CollisionHit c_hit = CollisionHit() );
         ~CollisionVector();

   };
} //sdl_platformer
#endif // _COLLISION_VECTOR_
