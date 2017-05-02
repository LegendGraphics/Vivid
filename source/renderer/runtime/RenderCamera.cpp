#include "RenderCamera.h"

namespace te
{
    RenderObject::Type RenderCamera::TYPE = RenderObject::NOT_INITIALIZED;
    RenderCamera::RenderCamera(CameraData::ProjectionType type, float near_range, float far_range,
        const Mat4x4& projection, const Mat4x4& view)
        : RenderObject(TYPE)
    {
        setType(type);
        setRange(near_range, far_range);
        setMatrix(projection, view);
    }

    void RenderCamera::setType(CameraData::ProjectionType type)
    {
        _cameraData.type = type;
    }

    void RenderCamera::setRange(float near_range, float far_range)
    {
        _cameraData.nearRange = near_range;
        _cameraData.farRange = far_range;
    }

    void RenderCamera::setMatrix(const Mat4x4 & projection, const Mat4x4 & view)
    {
        _projection = projection;
        _view = view;
        _view_projection = _projection * _view;
    }

    void RenderCamera::setViewPort(int x0, int y0, int x1, int y1)
    {
        _viewPort[0] = x0;
        _viewPort[1] = y0;
        _viewPort[2] = x1;
        _viewPort[3] = y1;
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