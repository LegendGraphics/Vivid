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
        _view_projection = _projection * _view;
    }

    float* RenderCamera::getViewMat()
    {
        return &_view(0, 0);
    }

    float* RenderCamera::getProjectionMat()
    {
        return &_projection(0, 0);
    }

    float* RenderCamera::getViewProjctionMat()
    {
        return &_view_projection(0, 0);
    }

    int * RenderCamera::getViewPort()
    {
        return &_viewPort[0];
    }

}