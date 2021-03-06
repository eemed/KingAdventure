#ifndef _RECTANGLE_
#define _RECTANGLE_

#include "game_object.h"

namespace sdl_platformer
{
   class Rectangle : public GameObject
   {
      public:
         SDL_Rect m_rectangle;
         SDL_Rect m_source;
         Rectangle(int pos_x, int pos_y, int width, int height, Color color);
         Rectangle(int pos_x, int pos_y, int width, int height,
               SDL_Rect sprite);
         ~Rectangle();

         void set_width(int new_width);
         void set_height(int new_height);

         int get_width() const;
         int get_height() const;

         void set_x(int new_x);
         void set_y(int new_y);

         int get_x() const;
         int get_y() const;

         int get_x_high() const;
         int get_y_high() const;

         int get_x_middle() const;
         int get_y_middle() const;

         int get_x_low() const;
         int get_y_low() const;

         int get_half_x_len() const;
         int get_half_y_len() const;

         void draw() const;
         void move( Vector &, float elapsed_time);
         SDL_Rect get_rect() const;
         void move(float dx, float dy);
   };
} //namespace sdl_platformer
#endif // _RECTANGLE_
