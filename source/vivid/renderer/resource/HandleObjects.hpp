#ifndef VIVID_RENDERER_OBJECT_CONTAINER_H
#define VIVID_RENDERER_OBJECT_CONTAINER_H

#include <vector>

#include "vivid/base/Types.h"


namespace vivid
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
            if (has(handle))
            {
                delete _objects[handle - 1];
                _objects[handle - 1] = nullptr;
                _free_list.push_back(handle);
            }
        }

        bool has(Handle handle)
        {
            if (handle > _objects.size() || !_objects[handle - 1]) return false;
            else return true;
        }

        T* getPtr(Handle handle)
        {
            if (has(handle))
                return _objects[handle - 1];
            else return nullptr;
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
