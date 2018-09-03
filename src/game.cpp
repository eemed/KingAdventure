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

   Game::Game()
      :
      m_screen_manager( ScreenManager() ),
      m_factory( SpriteFactory() ),
      m_menu( NULL ),
      m_world( NULL ),
      m_network( 0 ),
      m_input( InputHandler() ),
      m_running( true )
   {
      std::vector< std::string > menu_items;
      menu_items.push_back("Play");
      menu_items.push_back("Quit");
      m_menu = new (Menu) (menu_items);
      activate();
      // TEST
      m_network = new Network;
      m_network->connect_to("localhost", "13371");
      m_network->send_message("Hello");
   }

   Game::~Game()
   {
      deactivate();
      delete m_network;
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
            update(dt);
            accumulator -= dt;
            updated = true;
         }

         if( updated )
         {
            //Draw world to current screen
            render();
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

   void
   Game::update(float dt)
   {
      if( m_world != 0 )
      {
         m_world->update(dt);
      }
      if( m_menu != NULL )
      {
         m_menu->update();
      }
   }

   void
   Game::render()
   {
      if( m_world != 0 )
      {
         m_screen_manager.m_screen.draw( *(m_world->get_render_context()) );
      }
      if( Menu::current() != 0 )
      {
         m_menu->draw();
      }
   }
   void
   Game::create_world(std::string filename)
   {
      m_world = new(World)(filename);
   }

   Menu *
   Game::get_menu()
   {
      return m_menu;
   }

   void
   Game::destroy_menu()
   {
      delete m_menu;
      m_menu = NULL;
   }
} //sdl_platformer
