#ifndef COMMON_CAMERA_H
#define COMMON_CAMERA_H

#include "common/Node.h"
#include "math/Vector3.h"

namespace te
{
    class Camera : public Node
    {
    public:
        enum class CameraMode
        {
            ORTHOGONAL,
            PERSPECTIVE
        };

    public:
        void setCameraMode(CameraMode mode);

        void setViewTransform(const Vector3& eye, const Vector3& center, const Vector3& up);
        void setViewTransform(float fov, float aspect, float znear, float zfar);
        void setOrthoTransform(float left, float right, float bottom, float top, float znear = -1.0, float zfar = 1.0);

    protected:
        CameraMode  _mode;
    };
}


#endif // COMMON_CAMERA_H