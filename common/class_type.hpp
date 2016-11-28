#ifndef COMMON_CLASS_TYPE_HPP
#define COMMON_CLASS_TYPE_HPP

#include <cstddef>

namespace te
{
    template <typename TBase>
    class ClassTypeId
    {
    public:

        template <typename T>
        static int getTypeId()
        {
            static const int id = _next_type_id++;
            return id;
        }

    private:
        static int _next_type_id;
    };

    template <typename TBase>
    int ClassTypeId<TBase>::_next_type_id = 0;

    template <class T>
    int getComponentTypeId()
    {
        return ClassTypeId<Component>::getTypeId<T>();
    }
}



#endif // COMMON_CLASS_TYPE_HPP