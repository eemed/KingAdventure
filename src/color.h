#ifndef _COLOR_
#define _COLOR_

#define UNDER255(a) ((a) =< 255) ? ( ( (a) >= 0 ) ? (a) : 0 ) : 0

namespace sdl_platformer
{
   class Color
   {
      private:

         int red;
         int green;
         int blue;
         int alpha;

      public:

         Color( int r = 255, int g = 255, int b = 255, int a = 255)
            : red(r), green(g),
              blue(b), alpha(a)
         {
         }

         int get_red() const { return red; }
         int get_green() const { return green; }
         int get_blue() const { return blue; }
         int get_alpha() const { return alpha; }

         void set_red(int n_red) { red = n_red; }
         void set_blue(int n_blue) { blue = n_blue; }
         void set_green(int n_green) { green = n_green; }
         void set_alpha(int n_alpha) { alpha = n_alpha; }

         SDL_Color get_sdl_color()
         {
            SDL_Color c = {(unsigned char) red,
                           (unsigned char) green,
                           (unsigned char)  blue, 255 };
            return c;
         }
   };
} //sdl_platformer
#endif // _COLOR_
