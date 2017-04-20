#ifndef IO_RESOURCE_LOADER_H
#define IO_RESOURCE_LOADER_H

#include "base/String.h"

namespace te
{
    class Mesh;
    class MetaNode;
    //class Pipeline;
    class ResourceLoader
    {
    public:
        static bool load(Mesh* mesh, const String& res);
        //static bool load(Pipeline* pipeline, const String& res);
        static bool load(MetaNode* meta_node, const String& res);
    };
}

#endif // IO_RESOURCE_LOADER_H