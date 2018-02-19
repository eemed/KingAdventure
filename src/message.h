#ifndef _MESSAGE_
#define _MESSAGE_

#include <string>
#include <cstdlib>

namespace sdl_platformer
{
   enum { HEADER_LEN = 4 };
   enum { MAX_MSG_LEN = 512 };

   class Message
   {
      private:
         std::string m_msg;
         std::string m_header;
         size_t m_msg_size;

      public:
         Message();
         Message(std::string msg);

         size_t length() const;
         const std::string data();
         std::string data();

         const std::string msg() const;
         std::string msg();
         void msg(std::string new_msg);

         const std::string header() const;
         std::string header();
         void header(std::string new_msg);

         size_t std::string msg_length() const;

         bool decode_header();
   };
} // sdl_platformer
#endif //_MESSAGE_
