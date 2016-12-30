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
        RenderCamera(CameraData::ProjectionType type, float near_range, float far_range,
            const Mat4x4& projection, const Mat4x4& view);

    private:
        Mat4x4 _view;
        Mat4x4 _projection;
        CameraData _cameraData;
    };
}

#endif
