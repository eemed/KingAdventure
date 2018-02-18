#include <iostream>

#include "connection.h"

using boost::asio::ip::tcp;

namespace sdl_platform
{
   Connection::Connection(
         boost::asio::io_service & io_service,
         tcp::resolver::iterator endpoint_iterator)
      : m_io_service( io_service ),
        m_socket( io_service )
   {
      boost::asio::async_connect(
            m_socket,
            endpoint_iterator,
            boost::bind(
               &Connection::connect,
               this,
               boost::asio::placeholders::error) );
   }

   Connection::~Connection()
   {
   }

   void
   Connection::write(const Message& msg)
   {
      m_io_service.post(boost::bind(&Connection::do_write, this, msg) );
   }

   void
   Connection::close()
   {
      m_io_service.post(boost::bind(&Connection::do_close, this) );
   }

   void 
   connect(const boost::system::error_code& error)
   {
     if (!error)
     {
       boost::asio::async_read(
             m_socket,
             boost::asio::buffer(read_msg_.data(), chat_message::header_length),
             boost::bind(
                &Connection::handle_read_header,
                this,
                boost::asio::placeholders::error) );
     }
   }
   
   void handle_read_header(const boost::system::error_code& error)
   {
     if (!error && read_msg_.decode_header())
     {
       boost::asio::async_read(socket_,
           boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
           boost::bind(&chat_client::handle_read_body, this,
             boost::asio::placeholders::error));
     }
     else
     {
       do_close();
     }
   }
   
   void handle_read_body(const boost::system::error_code& error)
   {
     if (!error)
     {
       std::cout.write(read_msg_.body(), read_msg_.body_length());
       std::cout << "\n";
       boost::asio::async_read(socket_,
           boost::asio::buffer(read_msg_.data(), chat_message::header_length),
           boost::bind(&chat_client::handle_read_header, this,
             boost::asio::placeholders::error));
     }
     else
     {
       do_close();
     }
   }
   
   void do_write(chat_message msg)
   {
     bool write_in_progress = !write_msgs_.empty();
     write_msgs_.push_back(msg);
     if (!write_in_progress)
     {
       boost::asio::async_write(socket_,
           boost::asio::buffer(write_msgs_.front().data(),
             write_msgs_.front().length()),
           boost::bind(&chat_client::handle_write, this,
             boost::asio::placeholders::error));
     }
   }
   
   void handle_write(const boost::system::error_code& error)
   {
     if (!error)
     {
       write_msgs_.pop_front();
       if (!write_msgs_.empty())
       {
         boost::asio::async_write(socket_,
             boost::asio::buffer(write_msgs_.front().data(),
               write_msgs_.front().length()),
             boost::bind(&chat_client::handle_write, this,
               boost::asio::placeholders::error));
       }
     }
     else
     {
       do_close();
     }
   }
   
   void do_close()
   {
     socket_.close();
   }
}
