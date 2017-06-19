#ifndef RENDERER_RENDER_CAMERA_H
#define RENDERER_RENDER_CAMERA_H

#include "vivid/renderer/runtime/RenderObject.h"
#include "vivid/math/Matrix.h"

namespace te
{
    struct CameraData
    {
        enum ProjectionType : uint8
        {
            ORTHOGRAPHIC,
            PERSPECTIVE
        };

        float near_range;
        float far_range;
        ProjectionType type;
    };

    class RenderCamera : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;
        RenderCamera() = default;
        RenderCamera(CameraData::ProjectionType type, float near_range, float far_range,
            const Matrix& projection, const Matrix& view);

        void setType(CameraData::ProjectionType type);
        void setRange(float near_range, float far_range);
        void setMatrix(const Matrix& projection, const Matrix& view);
        void setViewPort(int x0, int y0, int x1, int y1);

        float* getViewMat();
        float* getProjectionMat();
        float* getViewProjctionMat();
        int* getViewPort();

    private:
        Matrix _view;
        Matrix _projection;
        Matrix _view_projection;
        int    _view_port[4];
        CameraData _camera_data;
    };
}

#endif
