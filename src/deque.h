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

   template<typename T>
   Deque<T>::Deque()
   {
   }

   template<typename T>
   T * Deque<T>::front()
   {
      T * pointer;
      std::lock_guard<std::mutex> lock(m_mutex);
      pointer = &(m_deq.front());
      return pointer;
   }

   template<typename T>
   void Deque<T>::pop_front()
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_deq.pop_front();
   }

   template<typename T>
   void Deque<T>::push_back( T &new_elem )
   {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_deq.push_back(new_elem);
   }
}
#endif // _DEQUE_
