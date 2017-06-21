
#include "vivid/common/Camera.h"

#include "vivid/common/SpaceState.h"
#include "vivid/base/EventDispatcher.h"
#include "vivid/base/Director.h"
#include "vivid/io/ResourceLoader.h"

namespace vivid
{
    const Vector3 WorldCoordinate::WORLD_UP(0, 1, 0);
    const Vector3 WorldCoordinate::WORLD_RIGHT(1, 0, 0);
    const Vector3 WorldCoordinate::WORLD_FORWARD(0, 0, -1);


    Camera* Camera::create(const String& res)
    {
        return dynamic_cast<Camera*>(Node::create(res));
    }

    Camera::Camera()
    {
        _node_type = NodeType::CAMERA;
        addComponent<CameraState>();
    }

    Camera::Camera(const Camera& node, const CopyOperator& copyop)
    {
        copyop(&node);
    }

    Camera::~Camera(){}

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

    CameraState* CameraState::create(const String& res)
    {
        CameraState* cs = new CameraState;
        ResourceLoader::load(cs, res);
        return cs;
    }


    CameraState::CameraState()
        :ComData(ComponentType::CAMERA_STATE)
    {}

    CameraState::~CameraState(){}


    void CameraState::setCameraMode(CameraMode mode)
    {
        _mode = mode;
    }

    void CameraState::setViewPort(const Vector4& view_port)
    {
        _view_port = view_port;
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


    FocusCamera::FocusCamera()
        :_focused(false)
    {
        connect(ListenType::MOUSE_LEFT, this, &FocusCamera::onMouseLeft);
        connect(ListenType::MOUSE_MIDDLE, this, &FocusCamera::onMouseMiddle);

        addComponent<FocusCameraBehavior>();
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
            _focused = true;
        }
        else if (mouse_event->mouseEventType() == MouseEvent::MouseEventType::MOUSE_UP)
        {
            _focused = false;
        }
    }

    void FocusCamera::onMouseMiddle(Event* event)
    {

    }

    FocusCameraBehavior::FocusCameraBehavior()
        :Behavior(ComponentType::LOGIC_BEHAVIOR)
    {}

    void FocusCameraBehavior::update()
    {
        FocusCamera* focus_camera = dynamic_cast<FocusCamera*>(_owner);
        if (focus_camera->isFocused())
        {
            Vector2 cur_pos = Director::getInstance()->getCurMousePos();
            Vector2 last_pos = focus_camera->getFocusMousePos();
            CameraState* state = focus_camera->getComponent<CameraState>();

            float x_diff = (cur_pos.x - last_pos.x) * 0.005;
            float y_diff = (cur_pos.y - last_pos.y) * 0.005;

            Transform x_diff_rotation = Transform::rotateY(x_diff);
            Transform y_diff_rotation = Transform::rotateX(y_diff);

            CameraState::CameraViewParas& view_paras = state->getViewParas();
            Vector3 delta_dist = (view_paras.position - view_paras.center);
            Vector3 dir = delta_dist.normalized();
            float dist = delta_dist.length();
            Vector3 new_pos = x_diff_rotation * y_diff_rotation * dir * dist + view_paras.center;
            view_paras.position = new_pos;
        }
    }
}