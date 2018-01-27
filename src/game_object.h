#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include <SDL2/SDL.h>
#include <string>

#include "vector.h"
#include "color.h"

namespace sdl_platformer
{
   class GameObject
   {
      protected:

         int m_pos_x;
         int m_pos_y;
         Color m_color;

      public:

         GameObject(int pos_x, int pos_y, Color color);
         ~GameObject();

         virtual int get_x() const;
         virtual int get_y() const;
         Color get_color() const;

         virtual void set_x(int new_x);
         virtual void set_y(int new_y);
         void set_color(Color new_color);

         virtual void draw() const = 0;

         //virtual void move( Vector &, float elapsed_time) = 0;
   };
} // namespace sdl_platformer
#endif //_GAME_OBJECT_
