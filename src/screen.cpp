#include <iostream>

#include "screen.h"
#include "world.h"

namespace sdl_platformer
{

   void
   setup_renderer(SDL_Renderer * renderer, const int & size_x, const int & size_y)
   {
       SDL_RenderSetLogicalSize( renderer, size_x, size_y );
       SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
   }

   SDL_Window *
   create_window(int & x, int & y, int & w, int & h)
   {
        SDL_Window * window =
           SDL_CreateWindow("Tetris", x, y, w, h, 0);
        if (window == nullptr){
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return NULL;
        }
        return window;
   }

   SDL_Renderer *
   create_renderer( SDL_Window * window)
   {
        SDL_Renderer * renderer =
           SDL_CreateRenderer(window, -1,
                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr){
            SDL_DestroyWindow(window);
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return NULL;
        }
        return renderer;
   }

   //Screen * Screen::m_current = NULL;

   Screen::Screen(int x, int y, int width, int height)
      : m_window( create_window(x, y, width, height) ),
        m_renderer( create_renderer( m_window ) )
   {
      setup_renderer(m_renderer, width, height);
      activate();
   }

   Screen::~Screen()
   {
      deactivate();
      //Destroy everything
   }

   void
   Screen::draw( RenderContext & ctx ) const
   {
      SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
      SDL_RenderClear( m_renderer );
      ctx.draw();

      World::current()->get_player().draw();
      // Render the changes above
      SDL_RenderPresent( m_renderer );
   }

   //Screen *
   //Screen::current() { return m_current; }

   //void
   //Screen::select()
   //{
   //   m_current = this;
   //}

   SDL_Renderer *
   Screen::get_renderer()
   {
      return m_renderer;
   }
}// sdl_platformer
