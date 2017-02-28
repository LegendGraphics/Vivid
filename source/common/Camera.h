#ifndef COMMON_CAMERA_H
#define COMMON_CAMERA_H

#include "common/Node.h"
#include "common/Component.h"
#include "math/Vector3.h"
#include "math/Transform.h"
#include "shape/Frustum.h"

namespace te
{
    // Consider Camera as a special leaf node
    class Camera : public Node
    {
    public:
        ENABLE_LEAF_NODE
        Camera();
        virtual ~Camera();

        bool cull(Node* node);

    private:
        void initComponents();
        bool frustumCullingImpl(Node* node);
        
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
        const Frustum& getFrustum();

    protected: 
        CameraRefCoord      _camera_ref;
        CameraPesParas      _pes_paras;
        CameraOrthoParas    _ortho_paras;
        Frustum             _frustum;

        CameraMode          _mode;
    };
}


#endif // COMMON_CAMERA_H