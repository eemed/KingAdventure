#include "deque.h"

namespace sdl_platformer
{
   template<typename T>
   Deque<T>::Deque()
   {
   }

   template<typename T>
   T * Deque<T>::front()
   {
      T * pointer;
      m_mutex.lock();
      pointer = &(m_deq.front());
      m_mutex.unlock();
      return pointer;
   }

   template<typename T>
   void Deque<T>::pop_front()
   {
      m_mutex.lock();
      m_deq.pop_front();
      m_mutex.unlock();
   }

   template<typename T>
   void Deque<T>::push_back( T &new_elem )
   {
      m_mutex.lock();
      m_deq.push_back(new_elem);
      m_mutex.unlock();
   }
} // sdl_platformer
