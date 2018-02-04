#ifndef _RENDER_CONTEXT_
#define _RENDER_CONTEXT_

#include <vector>
#include <string>

#include "rectangle.h"
#include "circle.h"

namespace sdl_platformer
{
   class RenderContext
   {
      public:
         std::vector< Rectangle > m_squares;
         std::vector< Circle > m_circles;
         std::vector< Rectangle > m_decor_back;
         SDL_Texture * m_bg;
         SDL_Rect m_bg_rect;

         RenderContext(std::string filename);
         ~RenderContext();

         void update(std::vector< Rectangle > ,
              std::vector< Circle > );

         void update_circles(std::vector< Circle > );
         void update_squares(std::vector< Rectangle > );

         void draw() const;
         void move(float dx, float dy);

         bool load_from_json(std::string filename);
   };
} // namespace sdl_platformer
#endif //_RENDER_CONTEXT_
