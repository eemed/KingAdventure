#ifndef _CONNECTION_
#define _CONNECTION_

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>

#include "current.h"

namespace sdl_platform
{
   class Connection : Current<Connection>
   {
      private:
         boost::asio::ioservice & m_io_service;
         tcp::socket m_socket;
         std::deque<Message> m_write_msgs;
         Message m_read_msg;

      public:
         Connection();
         ~Connection();

         void close();
         bool connect();
         void handle_read_header(const boost::system::error_code& error);
         void handle_read_body(const boost::system::error_code& error);
         void do_write(Message msg);
         void handle_write(const boost::system::error_code& error);
         void do_close();
   };
}
#endif //_CONNECTION_
