#ifndef _GENERATOR_
#define _GENERATOR_

#include <cstdlib>
#include <vector>
#include <string>

#include "rectangle.h"

namespace sdl_platformer
{
   //Return created filename
   std::string generate_world(unsigned int seed, int width);

   bool write_to_file( std::string name,
                       std::vector< Rectangle > m_hitboxes//,
                       //std::vector< Rectangle > m_decor_back,
                       //std::vector< Rectangle > m_decor_top );
                       );
} //sdl_platformer
#endif //_GENERATOR_
