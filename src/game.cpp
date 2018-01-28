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
      : m_screen( Screen() ),
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
      const double dt = 0.01;
      int prevTime = 0;
      int currentTime = SDL_GetTicks();
      float deltaTime = 0;
      double accumulator = 0;
      while( m_running )
      {
          prevTime = currentTime;
          currentTime = SDL_GetTicks();
          deltaTime = (currentTime - prevTime) / 1000.0f;

          //Process input
          m_input.process_events(dt);

          accumulator += deltaTime;

          bool updated = false;

          if( accumulator >= dt )
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
      }
   }

   void
   Game::terminate()
   {
      m_running = false;
      //delete stuff
   }

   //Game *
   //Game::current() { return _current; }

   //void
   //Game::activate() { _current = this; }

   //void
   //Game::deactivate() { _current = NULL; }
} //sdl_platformer
