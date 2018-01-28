#ifndef _CURRENT_
#define _CURRENT_
namespace sdl_platformer
{
   template<class T>
   class Current
   {
      private:
         static T * _current;

      protected:
         Current()
         {
           _current = static_cast<T*>(this);
         }

         virtual ~Current()
         {
           if (_current == this)
           {
             _current = 0;
           }
         }

      public:
         static T * current() { return _current; }
         void activate() { _current = static_cast<T*>(this); }
         void deactivate() { _current = 0; }
   };
   template<class T> T* Current<T>::_current = 0;
} //sdl _platformer
#endif // current
