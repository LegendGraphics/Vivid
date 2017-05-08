#ifndef RENDERER_RENDEROBJECTCONTAINER_H
#define RENDERER_RENDEROBJECTCONTAINER_H

#include <vector>

#include "base/Types.h"


namespace te
{
    template<class T>
    class HandleObjects
    {
    public:
        ~HandleObjects() { clear(); }

        Handle add(T* obj)
        {
            if (!_free_list.empty())
            {
                Handle handle = _free_list.back();
                _free_list.pop_back();
                _objects[handle - 1] = obj;
                return handle;
            }
            else
            {
                _objects.push_back(obj);
                return (Handle)_objects.size();
            }
        }

        void remove(Handle handle)
        {
            if (!_objects[handle - 1]) return;
            delete _objects[handle - 1];
            _objects[handle - 1] = nullptr;
            _free_list.push_back(handle);
        }

        T* getPtr(Handle handle)
        {
            return _objects[handle - 1];
        }

        void clear()
        {
            for (T* ptr : _objects)
            {
                if (ptr) delete ptr;
            }
            _objects.clear();
            _free_list.clear();
        }

    private:
        std::vector<T*>     _objects;
        std::vector<Handle> _free_list;
    };
}

#endif
