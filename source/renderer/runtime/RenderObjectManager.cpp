#include "RenderObjectManager.h"

#include "renderer/RenderWorld.h"
#include "renderer/resource/RenderMeshObject.h"
#include "RenderCamera.h"

namespace te
{
    RenderObjectManager::RenderObjectManager() : _type(0)
    {
        register_objects();
    }

    void RenderObjectManager::register_objects()
    {
        RenderWorld::TYPE = alloc_type("WorldRenderInterface");
        RenderMeshObject::TYPE = alloc_type("MeshObject");
        RenderCamera::TYPE = alloc_type("Camera");
    }
}
