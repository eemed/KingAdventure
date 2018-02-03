#include <iostream>
#include <cmath>

#include "SDL2/SDL_image.h"
#include "player.h"
#include "collision.h"
#include "world.h"
#include "current.h"


namespace sdl_platformer
{
   Player::Player(int x, int y, int width, int height,
         Color col, std::string name, char_type t)
      : m_hitbox( Rectangle(x, y, width, height, col) ),
        m_physics( Physics()),
        m_state( PlayerState( name, NOT_JUMPING, false, true, RIGHT) ),
        m_sprite_manager( SpriteManager(t) )
   {
      m_dest.w = 64 + 32;
      m_dest.h = 64 + 32;
   }

   Player::~Player()
   {
   }

   std::string
   Player::get_name() const { return m_state.m_name; }

   bool
   Player::hits_ground() const { return m_state.m_on_ground; }

   jump_state
   Player::get_jump_state() const { return m_state.m_jump_state; }

   void
   Player::update(float elapsed_time)
   {
      m_physics.update(elapsed_time);

      float new_x = m_hitbox.get_x() + m_physics.get_velocity_x();
      float new_y = m_hitbox.get_y() + m_physics.get_velocity_y();

      // walking
      if( abs(m_physics.get_velocity_x()) > 1 )
      {
         m_sprite_manager.update_player(WALK, elapsed_time);
      }
      else
      {
         m_sprite_manager.force_update_player(IDLE);
      }

      if( m_physics.get_velocity_x() < 0 )
      {
         m_hitbox.set_x( ceil(new_x) );
      }
      else // >= 0
      {
         m_hitbox.set_x( floor(new_x) );
      }
      if( m_physics.get_velocity_y() < 0 )
      {
         m_hitbox.set_y( ceil(new_y) );
      }
      else // >= 0
      {
         m_hitbox.set_y( floor(new_y) );
      }
      set_jump_state();

      // Jumping
      if( m_state.m_jump_state == RISE )
      {
         m_sprite_manager.force_update_player(JUMP_RISE);
      }
      if( m_state.m_jump_state == FALL )
      {
         m_sprite_manager.force_update_player(JUMP_FALL);
      }

      fix_collision();
      m_dest.x = m_hitbox.get_x() - (m_dest.w - m_hitbox.get_width() ) / 2 - 1;
      m_dest.y = m_hitbox.get_y() - (m_dest.h - m_hitbox.get_height() ) ;
      update_facing();
      //std::cout << "Hbox: " << m_hitbox.get_x() << ", " << m_hitbox.get_y() << "\n";
   }

   void
   Player::update_facing()
   {
      if( m_physics.get_velocity_x() > 0 )
      {
         m_state.m_facing = RIGHT;
      }
      if( m_physics.get_velocity_x() < 0 )
      {
         m_state.m_facing = LEFT;
      }
   }
   void
   Player::set_jump_state()
   {
      if( hits_ground() )
      {
         m_state.m_jump_state = NOT_JUMPING;
      }
      else if( ceil(m_physics.get_velocity_y()) > 0 )
      {
         m_state.m_jump_state = FALL;
      }
      else if( m_physics.get_velocity_y() < 0 )
      {
         m_state.m_jump_state = RISE;
      }
      else if( m_state.m_jump_state == RISE
            and abs(m_physics.get_velocity_y()) < 0.3f)
      {
         m_state.m_jump_state = TOP;
      }
   }

   void
   Player::hits_ground(bool n_hits) { m_state.m_on_ground = n_hits; }

   void
   Player::fix_collision()
   {
      //Replace this with something that searches nearby
      //collidables. Now uses worlds rendecontext.
      World * cur = World::current();
      bool is_hit = false;
      // -2 means prefer y collisions
      // 3 means prefer x collisions
      int padding = ( hits_ground() or (m_state.m_jump_state == FALL) ) ? -2 : 3;
      if( !m_state.m_fly_mode )
      {
         m_hitbox.set_y( m_hitbox.get_y() + 1);
      }
      for( auto & elem : cur->get_render_context()->m_squares )
      {
         CollisionVector cv = rect_collides_with_rect( m_hitbox, elem, padding);
         if( cv.m_collision_info.m_bottom )
         {
            is_hit = true;
         }
         if( cv.m_collision_info.m_top )
         {
            m_physics.set_velocity_y(0.0f);
         }
         m_hitbox.set_y( m_hitbox.get_y() + cv.m_y );
         m_hitbox.set_x( m_hitbox.get_x() + cv.m_x );
      }
      if( !is_hit )
      {
         m_physics.set_gravity_enabled(true);
         hits_ground(false);
      }
      else
      {
         m_physics.set_gravity_enabled(false);
         hits_ground(true);
         m_physics.set_velocity_y(0.0f);
      }
   }

   void
   Player::move_right(float elapsed_time)
   {
      m_physics.move_right(elapsed_time);
   }

   void
   Player::move_left(float elapsed_time)
   {
      m_physics.move_left(elapsed_time);
   }

   void
   Player::move_up(float elapsed_time)
   {
      if( m_state.m_fly_mode )
      {
         m_physics.move_up(elapsed_time);
      }
   }

   void
   Player::move_down(float elapsed_time)
   {
      if( m_state.m_fly_mode )
      {
         m_physics.move_down(elapsed_time);
      }
   }

   void
   Player::speed_right(float elapsed_time)
   {
      m_physics.move_right(elapsed_time);
   }

   void
   Player::speed_left(float elapsed_time)
   {
      m_physics.move_left(elapsed_time);
   }

   void
   Player::jump()
   {
      if( hits_ground() )
      {
         m_physics.jump();
         m_state.m_jump_state = RISE;
      }
   }

   void
   Player::draw() const
   {
      //m_hitbox.draw();
      std::pair< SDL_Rect , SDL_Texture *> p = m_sprite_manager.get_player();
      //std::cout <<" x: " <<  p.first.x << "\n";
      //std::cout <<" y: " <<  p.first.y << "\n";
      //std::cout <<"d x: " <<  m_dest.x << "\n";
      //std::cout <<"d y: " <<  m_dest.y << "\n";
      SDL_RendererFlip flip =
         ( m_state.m_facing == RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
      SDL_RenderCopyEx(Screen::current()->get_renderer(),
            p.second, &p.first, &m_dest, 0, NULL, flip);
   }

   void
   Player::toggle_gravity()
   {
      if( m_physics.get_gravity_enabled() )
      {
         m_physics.set_gravity_enabled( !m_physics.get_gravity_enabled() );
         m_physics.enable_fly_mode();
         m_state.m_fly_mode = true;
         std::cout << "[PLAYER] Flymode Enabled\n";
      }
      else
      {
         m_physics.set_gravity_enabled( !m_physics.get_gravity_enabled() );
         m_physics.disable_fly_mode();
         m_state.m_fly_mode = false;
         std::cout << "[PLAYER] Flymode Disabled\n";
      }
   }

}// sdl_platformer
