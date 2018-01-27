#include "circle.h"

namespace sdl_platformer
{
   Circle::Circle(int pos_x, int pos_y, double radius, Color color)
      : GameObject(pos_x, pos_y, color), m_radius( radius )
   {
   }

   Circle::~Circle()
   {
   }

   void
   Circle::draw() const
   {
      return;
   }
}// sdl_platformer
