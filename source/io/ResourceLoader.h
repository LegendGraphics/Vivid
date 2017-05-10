#ifndef IO_RESOURCE_LOADER_H
#define IO_RESOURCE_LOADER_H

#include "utXML.h"
#include "base/String.h"

namespace te
{
    class Mesh;
    class MetaNode;
    class Pipeline;
    struct PipelineStage;
    class Texture;

    class ResourceLoader
    {
    public:
        static bool load(Mesh* mesh, const String& res);
        static bool load(Pipeline* pipeline, const String& res);
        static bool load(MetaNode* meta_node, const String& res);
        static bool load(Texture* texture, const String& res);

    // private function used by loader itself
    public:
        static const String parseStage(XMLNode &node, PipelineStage* cur_stage);
    };
}

#endif // IO_RESOURCE_LOADER_H