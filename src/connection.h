#ifndef _CONNECTION_
#define _CONNECTION_

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>

#include "current.h"

namespace sdl_platformer
{
   class Connection : Current<Connection>
   {
      private:
         boost::shared_ptr< boost::asio::io_service > m_io_service;
         boost::shared_ptr< boost::asio::ip::tcp::socket > m_socket;
         std::string m_connected_to;

         void handle_connect(const boost::system::error_code & ec);

      public:
   };
}
#endif //_CONNECTION_
