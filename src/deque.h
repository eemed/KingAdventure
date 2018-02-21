#ifndef _DEQUE_
#define _DEQUE_

#include <deque>
#include <mutex>

namespace sdl_platformer
{
   template<typename T>
   class Deque
   {
      private:
         std::mutex m_mutex;
         std::deque<T> m_deq;

      public:
         Deque();

         T * front();
         void pop_front();
         void push_back( T &new_elem );
   };
}
#endif // _DEQUE_
