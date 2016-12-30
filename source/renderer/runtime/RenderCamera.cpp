#include "RenderCamera.h"

namespace te
{
    RenderObject::Type RenderCamera::TYPE = RenderObject::NOT_INITIALIZED;
    RenderCamera::RenderCamera(CameraData::ProjectionType type, float near_range, float far_range,
        const Mat4x4& projection, const Mat4x4& view)
        : RenderObject(TYPE)
    {
        _cameraData.type = type;
        _cameraData.nearRange = near_range;
        _cameraData.farRange = far_range;

        _projection = projection;
        _view = view;
    }
}