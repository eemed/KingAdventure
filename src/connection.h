#ifndef _CONNECTION_
#define _CONNECTION_

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>

#include "deque.h"
#include "current.h"

namespace sdl_platformer
{
   class Connection : Current<Connection>
   {
      private:
         boost::shared_ptr< boost::asio::io_service > m_io_service;
         boost::shared_ptr< boost::asio::ip::tcp::socket > m_socket;
         Deque< Packet > m_recv;
         char * m_recv_msg;
         std::string m_connected_to;

         void handle_connect(const boost::system::error_code & ec);
         void handle_send(const boost::system::error_code & ec);
         void handle_recv(const boost::system::error_code & ec);
         void handle_recv_header(const boost::system::error_code & ec);
         void handle_recv_packet(const boost::system::error_code & ec);

      public:
   };
}
#endif //_CONNECTION_
