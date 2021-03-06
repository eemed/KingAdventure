#ifndef _SCREEN_
#define _SCREEN_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "render_context.h"
#include "current.h"
#include "render_context.h"

namespace sdl_platformer
{
   //Bring up a window and ability to render to it
   class Screen : public Current<Screen>
   {
      private:
         SDL_Window * m_window;
         SDL_Renderer * m_renderer;
         int m_width;
         int m_height;
         RenderContext m_ctx;
      public:
         Screen(int x = 0, int y = 0, int width = 1600, int height = 900);
         ~Screen();

         void draw( RenderContext & ) const;
         void resize(int width, int height);
         int get_width() const;
         int get_height() const;

         SDL_Renderer * get_renderer();
   };

   SDL_Window * createWindow(int x, int y, int width, int height);
   SDL_Renderer * createRenderer( SDL_Window * );

} // namespace sdl_platformer
#endif //_SCREEN_
