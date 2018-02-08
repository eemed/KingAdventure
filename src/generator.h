#ifndef _GENERATOR_
#define _GENERATOR_

#include <cstdlib>
#include <vector>
#include <string>

#include "rectangle.h"

namespace sdl_platformer
{
   struct Hitbox
   {
      int x;
      int y;
      int w;
      int h;
   };

   struct Decor
   {
      int x;
      int y;
      int w;
      int h;
      std::string sprite;
   };

   //Return created filename
   std::string generate_world(unsigned int seed, int width);

   bool write_to_file( std::string name,
                       std::vector< Hitbox > m_hitboxes,
                       std::vector< Decor > m_decor_back//,
                       //std::vector< Rectangle > m_decor_top );
                       );
} //sdl_platformer
#endif //_GENERATOR_
