#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>

#include "render_context.h"
#include "json.hpp"
#include "screen.h"
#include "sprite_factory.h"

using json = nlohmann::json;

namespace sdl_platformer
{
   RenderContext::RenderContext(std::string filename)
      :  m_bg(NULL)
   {
      if( !load_from_json(filename) )
      {
         std::cout << "Failed to parse json file\n";
      }
   }

   RenderContext::RenderContext()
      :  m_bg(NULL)
   {
   }

   RenderContext::~RenderContext()
   {
      if( m_bg != NULL )
      {
         SDL_DestroyTexture(m_bg);
      }
   }

   void
   RenderContext::update(std::vector< Rectangle > n_sq,
         std::vector< Circle > n_circles )
   {
      m_squares = n_sq;
      m_circles = n_circles;
   }

   void
   RenderContext::update_circles(std::vector< Circle > n_circles)
   {
      m_circles = n_circles;
   }

   void
   RenderContext::update_squares(std::vector< Rectangle > n_sq)
   {
      m_squares = n_sq;
   }

   void
   RenderContext::draw() const
   {
      if( m_bg != NULL )
      {
         SDL_RenderCopy(
               Screen::current()->get_renderer(),
               m_bg,
               &m_bg_rect, &m_bg_rect);
      }
      //for( const auto & elem : m_squares)
      //{
      //   elem.draw();
      //}
      for( const auto & elem : m_circles)
      {
         elem.draw();
      }
      for( const auto & elem : m_decor_back)
      {
         elem.draw();
      }
      for( const auto & elem : m_text)
      {
         SDL_RenderCopy(
               Screen::current()->get_renderer(),
               elem.second,
               nullptr,
               &elem.first);
      }
   }

   bool
   RenderContext::load_from_json(std::string filename)
   {
      std::ifstream file_stream(filename);
      json parsed;
      file_stream >> parsed;
      for( auto & elem : parsed["squares"] )
      {
         m_squares.push_back(
              Rectangle( elem["x"], elem["y"],
                         elem["w"], elem["h"],
                         Color(200, 200, 200, 255) ) );
      }
      for( auto & elem : parsed["circles"] )
      {
         m_circles.push_back(
               Circle( elem["x"], elem["y"],
                       elem["r"], Color( 200, 200, 200, 255) ) );
      }
      for( auto & elem : parsed["decor_back"] )
      {
         m_decor_back.push_back(
               Rectangle( elem["x"], elem["y"],
                          elem["w"], elem["h"],
                          SpriteFactory::current()->get_sprite(elem["texture"]) ) );
      }
      std::string path = parsed["background"];
      SDL_Surface * surface = IMG_Load( path.c_str() );
      m_bg = SDL_CreateTextureFromSurface(
            Screen::current()->get_renderer(), surface);
      SDL_FreeSurface(surface);
      m_bg_rect.x = 0;
      m_bg_rect.y = 0;
      m_bg_rect.w = Screen::current()->get_width();
      m_bg_rect.h = Screen::current()->get_height();
      return true;
   }

   void
   RenderContext::move(float dx, float dy)
   {
      if( dx != 0 or dy != 0 )
      {
         for( auto & elem : m_squares)
         {
            elem.move(dx,dy);
         }
         for( auto & elem : m_decor_back)
         {
            elem.move(dx, dy);
         }
      }
   }
}// sdl_platformer
