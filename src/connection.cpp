#include "connection.h"

namespace sdl_platform
{
   Connection::Connection(std::string ip, int port)
      : m_ip(ip), m_port(port)
   {
   }

   Connection::~Connection()
   {
   }

   bool
   Connection::connect()
   {
   }
}
