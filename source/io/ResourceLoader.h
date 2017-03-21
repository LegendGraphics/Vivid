#ifndef IO_RESOURCE_LOADER_H
#define IO_RESOURCE_LOADER_H

#include <string>

namespace te
{
    class Mesh;
    //class Pipeline;
    class ResourceLoader
    {
    public:
        static bool load(Mesh* mesh, const std::string& res);
        //static bool load(Pipeline* pipeline, const std::string& res);
    };
}

#endif // IO_RESOURCE_LOADER_H