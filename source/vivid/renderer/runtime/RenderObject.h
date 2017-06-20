#ifndef RENDERER_RENDER_OBJECT_H
#define RENDERER_RENDER_OBJECT_H

#include "vivid/base/Types.h"

namespace vivid
{
    struct RenderObject
    {
        enum { NOT_INITIALIZED = 0xffffffff };
        typedef uint32 Type; // TODO: Type may use something in Common/

        RenderObject() : type(NOT_INITIALIZED) {};
        RenderObject(Type type_) : type(type_) {};
        virtual ~RenderObject() {};

        Type type;
    };
}


#endif
