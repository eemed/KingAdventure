#include "message.h"

namespace sdl_platformer
{
   Message::Message() : m_msg_size(0)
   {
   }

   Message::Message(std::string msg)
      : m_msg(msg),
        m_msg_size( msg.size() ),
        m_header( std::string("0000") )
   {
   }

   size_t
   Message::length() const
   {
      return m_msg_size + HEADER_LEN;
   }

   const std::string
   Message::data() const
   {
      return m_header + m_msg;
   }

   std::string
   Message::data()
   {
      return m_header + m_msg;
   }

   const std::string
   Message::msg() const
   {
      return m_msg;
   }

   std::string
   Message::msg()
   {
      return m_msg;
   }

   void
   Message::msg(std::string new_msg)
   {
      m_msg = new_msg;
      m_msg_size = new_msg.size();
   }

   const std::string
   Message::header() const
   {
      return m_header;
   }

   std::string
   Message::header()
   {
      return m_header;
   }

   void
   Message::header(std::string new_header)
   {
      if( new_header.size() == HEADER_LEN )
      {
         m_header = new_header;
      }
   }

   size_t
   Message::std::string msg_length() const
   {
      return m_msg_size;
   }

   bool
   Message::decode_header()
   {

   }
} // sdl_platformer
