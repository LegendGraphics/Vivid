#ifndef IO_RESOURCE_LOADER_H
#define IO_RESOURCE_LOADER_H

#include "base/String.h"

namespace te
{
    class Mesh;
    //class Pipeline;
    class ResourceLoader
    {
    public:
        static bool load(Mesh* mesh, const String& res);
        //static bool load(Pipeline* pipeline, const String& res);
    };
}

#endif // IO_RESOURCE_LOADER_H