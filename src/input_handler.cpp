#include <iostream>

#include "input_handler.h"
#include "game.h"
#include "menu.h"
#include "world.h"

namespace sdl_platformer
{
   //InputHandler * InputHandler::_current = NULL;

   InputHandler::InputHandler()
      : m_keyboard( SDL_GetKeyboardState(NULL) )
   {
      activate();
   }

   InputHandler::~InputHandler()
   {
      deactivate();
   }

   void
   InputHandler::update_events()
   {
      SDL_PumpEvents();
   }

   void
   InputHandler::process_menu_events()
   {
      SDL_Event event;
      while( SDL_PollEvent( &event ) )
      {
         if( event.type == SDL_QUIT )
         {
            Game::current()->terminate();
            break;
         }
         else if( event.type == SDL_KEYDOWN )
         {
            switch( event.key.keysym.sym )
            {
               case SDLK_q:
                  Game::current()->terminate();
                  break;
               case SDLK_UP:
                  Game::current()->get_menu()->move_up();
                  break;
               case SDLK_DOWN:
                  Game::current()->get_menu()->move_down();
                  break;
               case SDLK_SPACE:
                  Game::current()->get_menu()->select();
                  break;
               default:
                  break;
            }
         }
      }
   }

   void
   InputHandler::process_player_events(const float & elapsed_time)
   {
      if( m_keyboard[SDL_SCANCODE_RIGHT] and m_keyboard[SDL_SCANCODE_A])
         World::current()->get_player()->speed_right(elapsed_time);
      else if( m_keyboard[SDL_SCANCODE_RIGHT] )
         World::current()->get_player()->move_right(elapsed_time);
      if( m_keyboard[SDL_SCANCODE_LEFT] and m_keyboard[SDL_SCANCODE_A])
         World::current()->get_player()->speed_left(elapsed_time);
      else if( m_keyboard[SDL_SCANCODE_LEFT] )
         World::current()->get_player()->move_left(elapsed_time);
      if( m_keyboard[SDL_SCANCODE_Q] )
         Game::current()->terminate();
      if( m_keyboard[SDL_SCANCODE_UP] )
         World::current()->get_player()->move_up(elapsed_time);
      if( m_keyboard[SDL_SCANCODE_DOWN] )
         World::current()->get_player()->move_down(elapsed_time);

      SDL_Event event;
      while( SDL_PollEvent( &event ) )
      {
         if( event.type == SDL_QUIT )
         {
            Game::current()->terminate();
            break;
         }
         else if( event.type == SDL_KEYDOWN )
         {
            switch( event.key.keysym.sym )
            {
               case SDLK_SPACE:
                  World::current()->get_player()->jump();
                  break;
               case SDLK_f:
                  World::current()->get_player()->toggle_gravity();
                  break;
               default:
                  break;
            }
         }
      }
   }

   void
   InputHandler::process_events(const float & elapsed_time)
   {
      update_events();
      if( Menu::current() != 0   )
      {
         process_menu_events();
      }
      else if( World::current() != 0 )
      {
         process_player_events( elapsed_time );
      }
      else
      {
         SDL_Event event;
         while( SDL_PollEvent( &event ) )
         {
            if( event.type == SDL_QUIT )
            {
               Game::current()->terminate();
               break;
            }
            else if( event.type == SDL_KEYDOWN )
            {
               switch( event.key.keysym.sym )
               {
                  case SDLK_q:
                     Game::current()->terminate();
                     break;
                  default:
                     break;
               }
            }
         }
      }
   }
} // sdl_platformer
