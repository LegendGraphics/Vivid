#ifndef IO_RESOURCE_LOADER_H
#define IO_RESOURCE_LOADER_H

#include "utXML.h"
#include "vivid/base/String.h"

namespace te
{
    class Mesh;
    class MetaNode;
    class Pipeline;
    struct PipelineStage;
    class Texture;
    class Material;
    class Shader;
    class CameraState;

    // currently use simply string
    // in the future we need FileSystem which could be made by python
    const String ASSETS_PATH = "Assets/";

    class ResourceLoader
    {
    public:
        static void setDataPath(const String& data_path);
        static bool load(Mesh* mesh, const String& res);
        static bool load(Pipeline* pipeline, const String& res);
        static bool load(MetaNode* meta_node, const String& res);
        static bool load(Texture* texture, const String& res);
        static bool load(Material* material, const String& res);
        static bool load(Shader* shader, const String& res);

    // private function used by loader itself
    public:
        static const String parseStage(XMLNode& node, PipelineStage* cur_stage);
        static const String parseGLSL(const String& res);

        static bool load(CameraState* camera_state, const String& res);

        static String _data_path;
    };
}

#endif // IO_RESOURCE_LOADER_H