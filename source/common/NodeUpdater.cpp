#include "common/NodeUpdater.h"
#include "common/Node.h"
#include "common/Camera.h"
#include "base/Director.h"

namespace te
{

    void FocusCameraUpdater::update(Node* node)
    {
        FocusCamera* focus_camera = dynamic_cast<FocusCamera*>(node);

        Vector2 cur_pos = Director::getInstance()->getCurMousePos();
        Vector2 last_pos = focus_camera->getFocusMousePos();
        CameraState* state = focus_camera->getComponent<CameraState>();

        float x_diff = cur_pos.x - last_pos.x;
        float y_diff = cur_pos.y - last_pos.y;

        Transform x_diff_rotation = Transform::rotateY(x_diff);
        Transform y_diff_rotation = Transform::rotateX(y_diff);

        CameraState::CameraViewParas& view_paras = state->getViewParas();
        Vector3 delta_dist = (view_paras.center - view_paras.position);
        Vector3 dir = delta_dist.normalized();
        float dist = delta_dist.length();
        Vector3 new_pos = x_diff_rotation * y_diff_rotation * dir * dist;
        view_paras.position = new_pos;
    }

    void CullingUpdater::update(Node* node)
    {
        
    }

    void RenderingUpdater::update(Node* node)
    {
        
    }


    
}
