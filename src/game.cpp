#include "game.h"
#include "SDL2/SDL.h"

#include <iostream>

namespace sdl_platformer
{
   bool
   init_sdl()
   {
      if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
      {
         std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
         return false;
      }
      return true;
   }

   //Game * Game::_current = NULL;

   Game::Game( std::string world_txt )
      :
      m_screen( Screen() ),
      m_factory( SpriteFactory() ),
      m_menu( Menu(std::vector<std::string>(1,"Start") ) ),
      m_world( World( world_txt )),
      m_running( true )
   {
      activate();
      m_menu.deactivate();
   }

   Game::~Game()
   {
      deactivate();
   }

   void
   Game::run()
   {
      const double dt = 0.0078125;
      int prev_time = 0;
      int current_time = SDL_GetTicks();
      float delta_time = 0;
      double accumulator = 0;
      while( m_running )
      {
         prev_time = current_time;
         current_time = SDL_GetTicks();
         delta_time = (current_time - prev_time) / 1000.0f;
         if( delta_time > 0.1 )
         {
            delta_time = 0.1;
         }

         //Process input
         m_input.process_events(delta_time);

         accumulator += delta_time;

         bool updated = false;

         while( accumulator >= dt )
         {
            //update logic
            m_world.update(dt);
            accumulator -= dt;
            updated = true;
         }

         if( updated )
         {
            //Draw world to current screen
            m_screen.draw( *m_world.get_render_context() );
         }
         else
         {
            SDL_Delay(1);
         }
      }
   }

   void
      Game::terminate()
      {
         m_running = false;
         //delete stuff
      }
} //sdl_platformer
