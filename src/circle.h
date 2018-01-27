#ifndef _CIRCLE_
#define _CIRCLE_

#include "game_object.h"

namespace sdl_platformer
{
   class Circle : public GameObject
   {
      protected:

          double m_radius;

      public:

         Circle(int pos_x, int pos_y, double radius , Color color);
         ~Circle();

         void draw() const;
   };
} // namepace sdl_platformer
#endif // _CIRCLE_
