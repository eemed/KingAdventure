#ifndef _COLLISION_
#define _COLLISION_

#include "collision_vector.h"
#include "rectangle.h"
#include "circle.h"

namespace sdl_platformer
{
   /*
    * Check collision and return a fix vector for the first object
    * to avoid collision. In air functions try not to correct upwards
    * if possible
    */
   CollisionVector rect_collides_with_rect( const Rectangle &, const Rectangle &, int padding);

   CollisionVector rect_collides_with_rect_in_air( const Rectangle &, const Rectangle &);

   CollisionVector rect_collides_with_circle( const Rectangle &, const Circle &);

   CollisionVector rect_collides_with_circle_in_air( const Rectangle &, const Circle &);
} //sdl_platformer
#endif // _COLLISION_
