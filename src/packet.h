#ifndef _PACKET_
#define _PACKET_

#include <string>


namespace sdl_platformer
{

   // Meanings for different packages
   enum type { CHAT, PLAYER };

   class Packet
   {
      public:
         enum { HEADER_LEN = 4 };

      private:
         std::string m_data;
         type m_type;

      public:
         Packet();
         bool parse_from(std::string s);

   };
} // sdl_platformer
#endif // _PACKET_
