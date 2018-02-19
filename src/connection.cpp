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
               boost::asio::buffer(m_read_msg.data().c_str(), Message::header_length),
               boost::bind(
                  &Connection::handle_read_header,
                  this,
                  boost::asio::placeholders::error) );
      }
   }

   void
   handle_read_header(const boost::system::error_code& error)
   {
      if (!error && m_read_msg.decode_header())
      {
         boost::asio::async_read(m_socket,
               boost::asio::buffer(m_read_msg.msg().c_str(), m_read_msg.msg_length() ),
               boost::bind(&Connection::handle_read_body,
                  this,
                  boost::asio::placeholders::error) );
      }
      else
      {
         do_close();
      }
   }

   void
   handle_read_body(const boost::system::error_code& error)
   {
      if (!error)
      {
         //DO THE STUFF TO MESSAGE
         std::cout.write(m_read_msg.msg(), m_read_msg.msg_length());
         std::cout << "\n";
         // -------

         boost::asio::async_read(m_socket,
               boost::asio::buffer(m_read_msg.data().c_str(), Message::HEADER_LEN),
               boost::bind(&Connection::handle_read_header,
                  this,
                  boost::asio::placeholders::error));
      }
      else
      {
         do_close();
      }
   }

   void
   do_write(Message msg)
   {
      bool write_in_progress = !m_write_msgs.empty();
      m_write_msgs.push_back(msg);
      if (!write_in_progress)
      {
         boost::asio::async_write(m_socket,
               boost::asio::buffer(m_write_msgs.front().data().c_str(),
                  m_write_msgs.front().length()),
               boost::bind(&Connection::handle_write,
                  this,
                  boost::asio::placeholders::error));
      }
   }

   void
   handle_write(const boost::system::error_code& error)
   {
      if (!error)
      {
         m_write_msgs.pop_front();
         if (!m_write_msgs.empty())
         {
            boost::asio::async_write(m_socket,
                  boost::asio::buffer(m_write_msgs.front().data().c_str(),
                     m_write_msgs.front().length()),
                  boost::bind(&Connection::handle_write,
                     this,
                     boost::asio::placeholders::error));
         }
      }
      else
      {
         do_close();
      }
   }

   void
   do_close()
   {
      m_socket.close();
   }
}
