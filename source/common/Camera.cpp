
#include "common/Camera.h"

#include "common/SpaceState.h"
#include "base/EventDispatcher.h"
#include "base/Director.h"

namespace te
{
    const Vector3 WorldCoordinate::WORLD_UP(0, 1, 0);
    const Vector3 WorldCoordinate::WORLD_RIGHT(1, 0, 0);
    const Vector3 WorldCoordinate::WORLD_FORWARD(0, 0, -1);


    Camera::Camera()
    {
        initComponents();
    }

    Camera::~Camera(){}

    void Camera::initComponents()
    {
        addComponent<CameraState>();
        addComponent<SpaceState>();
    }

    bool Camera::cull(Node* node)
    {
        return frustumCullingImpl(node);
    }

    bool Camera::frustumCullingImpl(Node* node)
    {
        //BoundingBox bb from node
        CameraState* camera_state = getComponent<CameraState>();
        //return camera_state->getFrustum().cullBox(bb);
        return true;
    }

    FocusCamera::FocusCamera()
    {
        connect(ListenType::MOUSE_LEFT, this, &FocusCamera::onMouseLeft);
        connect(ListenType::MOUSE_MIDDLE, this, &FocusCamera::onMouseMiddle);
    }

    void FocusCamera::setFocusMousePos(const Vector2& pos)
    {
        _focus_mouse_pos = pos;
    }

    void FocusCamera::onMouseLeft(Event* event)
    {
        MouseEvent* mouse_event = dynamic_cast<MouseEvent*>(event);
        if (mouse_event->mouseEventType() == MouseEvent::MouseEventType::MOUSE_DOWN)
        {
            _focus_mouse_pos = Vector2(mouse_event->getX(), mouse_event->getY());
        }
    }

    void FocusCamera::onMouseMiddle(Event* event)
    {

    }

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

    void CameraState::setViewTransform(const CameraViewParas& view_paras)
    {
        _view_paras = view_paras;
    }
    void CameraState::setPersProjectTransform(const CameraPersParas& pers_paras)
    {
        _pers_paras = pers_paras;
    }
    void CameraState::setOrthoProjectTransform(const CameraOrthoParas& ortho_paras)
    {
        _ortho_paras = ortho_paras;
    }

    Transform CameraState::getViewTransform() const
    {
        return Transform::lookAt(_view_paras.position, _view_paras.center, _view_paras.up);
    }

    Transform CameraState::getProjectTransform() const
    {
        if (_mode == CameraMode::PERSPECTIVE)
        {
            return Transform::perspective(_pers_paras.fov, _pers_paras.aspect,
                _pers_paras.znear, _pers_paras.zfar);
        } 
        else
        {
            return Transform::ortho(_ortho_paras.left, _ortho_paras.right, _ortho_paras.bottom,
                _ortho_paras.top, _ortho_paras.znear, _ortho_paras.zfar);
        }
    }

    const Frustum& CameraState::getFrustum()
    {
        Transform view = getViewTransform();
        Transform proj = getProjectTransform();
        _frustum.buildFrustum(view.rawMatrix(), proj.rawMatrix());
        return _frustum;
    }
}