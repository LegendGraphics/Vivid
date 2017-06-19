#include "vivid/renderer/runtime/RenderObjectManager.h"

#include "vivid/renderer/RenderWorld.h"
#include "vivid/renderer/runtime/RenderMeshObject.h"
#include "vivid/renderer/runtime/RenderCamera.h"

#include "vivid/common/ClassType.hpp"

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