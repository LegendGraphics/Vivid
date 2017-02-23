
#include "common/Camera.h"

namespace te
{
    CameraState::CameraState(){}

    CameraState::~CameraState(){}

    void CameraState::init()
    {

    }

    void CameraState::update()
    {

    }

    void CameraState::setCameraMode(CameraMode mode)
    {
        _mode = mode;
    }

    Transform CameraState::getViewTransform() const
    {
        return Transform::lookAt(_camera_ref.position, _camera_ref.center, _camera_ref.up);
    }

    Transform CameraState::getProjectTransform() const
    {
        if (_mode == CameraMode::PERSPECTIVE)
        {
            return Transform::perspective(_pes_paras.fov, _pes_paras.aspect, 
                _pes_paras.znear, _pes_paras.zfar);
        } 
        else
        {
            return Transform::ortho(_ortho_paras.left, _ortho_paras.right, _ortho_paras.bottom,
                _ortho_paras.top, _ortho_paras.znear, _ortho_paras.zfar);
        }
    }
}