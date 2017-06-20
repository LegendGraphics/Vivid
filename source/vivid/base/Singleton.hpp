#ifndef BASE_SINGLETON_H
#define BASE_SINGLETON_H

#include "vivid/base/Assert.h"

namespace vivid
{
    template <typename T>
    class Singleton
    {
    public:
        static T* getInstance()
        {
            if (!_singleton)
            {
                _singleton = new T();
            }
            return _singleton;
        }
    protected:
        Singleton(void)
        {
            _singleton = static_cast<T*>(this);
        }
        ~Singleton()
        {
            ASSERT(_singleton);
            delete _singleton;
        }

    private:
        Singleton(const Singleton<T> &) = delete;
        Singleton& operator=(const Singleton<T> &) = delete;

    protected:
        static T* _singleton;
    };

}

#endif // BASE_SINGLETON_H