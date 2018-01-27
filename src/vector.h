#ifndef _VECTOR_
#define _VECTOR_

#include <SDL2/SDL.h>
#include "collision_hit.h"

namespace sdl_platformer
{
   class Vector
   {
      public:
         int m_x;
         int m_y;

         Vector(int x = 0, int y = 0);
         ~Vector();
   };
} // namespace sdl_platformer
#endif //_VECTOR_
