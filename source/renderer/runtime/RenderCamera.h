#ifndef RENDERER_RENDERCAMERA_H
#define RENDERER_RENDERCAMERA_H

#include "renderer/resource/RenderObject.h"
#include "math/Matrix.h"

namespace te
{
    struct CameraData
    {
        enum ProjectionType : uint8
        {
            ORTHOGRAPHIC,
            PERSPECTIVE
        };

        float nearRange;
        float farRange;
        ProjectionType type;
    };

    class RenderCamera : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;
        RenderCamera() = default;
        RenderCamera(CameraData::ProjectionType type, float near_range, float far_range,
            const Mat4x4& projection, const Mat4x4& view);

        void setType(CameraData::ProjectionType type);
        void setRange(float near_range, float far_range);
        void setMatrix(const Mat4x4& projection, const Mat4x4& view);
        void setViewPort(int x0, int y0, int x1, int y1);

        float* getViewMat();
        float* getProjectionMat();
        float* getViewProjctionMat();
        int* getViewPort();

    private:
        Mat4x4 _view;
        Mat4x4 _projection;
        Mat4x4 _view_projection;
        int    _viewPort[4];
        CameraData _cameraData;
    };
}

#endif
