#ifndef RENDERER_RENDEROBJECTMANAGER_H
#define RENDERER_RENDEROBJECTMANAGER_H

#include "renderer/resource/RenderObject.h"

namespace te
{
    class RenderObjectManager
    {
    public:
        RenderObjectManager();

        void register_objects();
    private:
        RenderObject::Type alloc_type(const char *name) { return _type++; }
        RenderObject::Type _type;
    };
}

#endif
