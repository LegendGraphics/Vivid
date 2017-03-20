#ifndef BASE_SINGLETON_H
#define BASE_SINGLETON_H

#include "base/Director.h"

namespace te
{
    template <typename T>
    class Singleton
    {
    public:
        static T* getInstance()
        {
            if (!_singleton)
            {
                _singleton = new T;
            }
            return _singleton;
        }
    private:
        Singleton(void){}
        ~Singleton()
        {
            delete _singleton;
        }
        Singleton(const Singleton<T> &) = delete;
        Singleton& operator=(const Singleton<T> &) = delete;

    protected:
        static T* _singleton;
    };

    template <typename T>
    T* Singleton<T>::_singleton = nullptr;

    using DirectorS = Singleton<Director>;
}

#endif // BASE_SINGLETON_H