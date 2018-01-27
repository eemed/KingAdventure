#include <cstdlib>

#include "collision.h"

namespace sdl_platformer
{
   CollisionVector
   rect_collides_with_rect( const Rectangle & a, const Rectangle & b)
   {
      CollisionHit info;
      if( b.get_y_high() < a.get_y_low() and b.get_y_low() > a.get_y_high() )
      {
         if( b.get_x_high() > a.get_x_low() and b.get_x_low() < a.get_x_high() )
         {
            //Crossing
            int dirX = ( a.get_x_middle() - b.get_x_middle() );
            int dirY = ( a.get_y_middle() - b.get_y_middle() );

            int dx = a.get_half_x_len() + b.get_half_x_len() - ( abs(dirX) );
            int dy = a.get_half_y_len() + b.get_half_y_len() - ( abs(dirY) );
            if( abs(dx) < abs(dy) )
            {
               if( dirX > 0 )
               {
                  info.m_left = true;
                  return CollisionVector(dx, 0, info);
               }
               else
               {
                  info.m_right = true;
                  return CollisionVector(-dx, 0, info);
               }
            }
            else
            {
               if( dirY > 0 )
               {
                  info.m_top = true;
                  return CollisionVector(0, dy, info);
               }
               else
               {
                  info.m_bottom = true;
                  return CollisionVector(0, -dy, info);
               }
            }
         }
      }
      return CollisionVector(0, 0, info);
   }


   CollisionVector
   rect_collides_with_circle( const Rectangle &, const Circle &)
   {
      CollisionHit info;
      return CollisionVector(0, 0, info);
   }

   CollisionVector rect_collides_with_circle_in_air( const Rectangle &, const Circle &)
   {
      CollisionHit info;
      return CollisionVector(0, 0, info);
   }
} // sdl_platformer
