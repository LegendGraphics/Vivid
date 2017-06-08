#include "renderer/runtime/RenderObjectManager.h"

#include "renderer/RenderWorld.h"
#include "renderer/resource/RenderMeshObject.h"
#include "renderer/runtime/RenderCamera.h"

#include "common/ClassType.hpp"

namespace te
{
    template <class T>
    RenderObject::Type getRenderObjectTypeId()
    {
        static_assert(std::is_base_of<RenderObject, T>(), "Requested class must be a RenderObject!");
        return (RenderObject::Type)ClassTypeId<RenderObject>::getTypeId<T>();
    }

    void render_object::register_objects()
    {
        RenderWorld::TYPE = getRenderObjectTypeId<RenderWorld>();
        RenderMeshObject::TYPE = getRenderObjectTypeId<RenderMeshObject>();
        RenderCamera::TYPE = getRenderObjectTypeId<RenderCamera>();
    }
}