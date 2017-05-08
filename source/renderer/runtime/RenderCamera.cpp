#include "renderer/runtime/RenderCamera.h"

namespace te
{
    RenderObject::Type RenderCamera::TYPE = RenderObject::NOT_INITIALIZED;
    RenderCamera::RenderCamera(CameraData::ProjectionType type, float near_range, float far_range,
        const Matrix& projection, const Matrix& view)
        : RenderObject(TYPE)
    {
        setType(type);
        setRange(near_range, far_range);
        setMatrix(projection, view);
    }

    void RenderCamera::setType(CameraData::ProjectionType type)
    {
        _camera_data.type = type;
    }

    void RenderCamera::setRange(float near_range, float far_range)
    {
        _camera_data.near_range = near_range;
        _camera_data.far_range = far_range;
    }

    void RenderCamera::setMatrix(const Matrix & projection, const Matrix & view)
    {
        _projection = projection;
        _view = view;
        _view_projection = _projection * _view;
    }

    void RenderCamera::setViewPort(int x0, int y0, int x1, int y1)
    {
        _view_port[0] = x0;
        _view_port[1] = y0;
        _view_port[2] = x1;
        _view_port[3] = y1;
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
        return &_view_port[0];
    }

}