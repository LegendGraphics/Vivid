#ifndef COMMON_CAMERA_H
#define COMMON_CAMERA_H

#include "common/Node.h"
#include "common/Component.h"
#include "math/Vector3.h"
#include "math/Transform.h"

namespace te
{
    // make Camera a special Node ??
    class Camera : public Node
    {

    };

    class CameraState : public Component
    {
    public:
        enum class CameraMode
        {
            ORTHOGONAL,
            PERSPECTIVE
        };

    public:
        struct CameraRefCoord
        {
            Vector3 position;
            Vector3 center;
            Vector3 up;
        };

        struct CameraPesParas
        {
            float fov;
            float aspect;
            float znear;
            float zfar;
        };

        struct CameraOrthoParas
        {
            float left;
            float right;
            float bottom;
            float top;
            float znear;
            float zfar;
        };

    public:
        CameraState();
        virtual ~CameraState();

        virtual void init();
        virtual void update();

        void setCameraMode(CameraMode mode);

        Transform getViewTransform() const;
        Transform getProjectTransform() const;

    protected: 
        CameraRefCoord      _camera_ref;
        CameraPesParas      _pes_paras;
        CameraOrthoParas    _ortho_paras;

        CameraMode          _mode;
    };
}


#endif // COMMON_CAMERA_H