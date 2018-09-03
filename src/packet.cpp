#include "packet.h"
namespace sdl_platformer
{
   Packet::Packet() : m_type(CHAT)
   {
   }

   bool
   Packet::parse_from( std::string s )
   {
      return true;
   }
} // sdl_platformer
