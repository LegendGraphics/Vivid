#ifndef RENDERER_RENDEROBJECT_H
#define RENDERER_RENDEROBJECT_H

#include "base/Globals.h"

namespace te
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
