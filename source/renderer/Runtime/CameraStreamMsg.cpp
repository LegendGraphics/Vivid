#include "renderer/runtime/StateStream.h"
#include "renderer/runtime/RenderCamera.h"

namespace te
{
    CameraStreamMsg::CameraStreamMsg()
    {
    }

    CameraStreamMsg::~CameraStreamMsg()
    {
        /*delete static_cast<Data*>(_data);
        _data = nullptr;*/
    }

    void CameraStreamMsg::create(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        //if (render_object)
        //{
        //    delete static_cast<Data*>(_data)->rmo;
        //    return;
        //}
        //render_object = static_cast<Data*>(_data)->rmo; // pass the ownership to RenderWorld
    }

    void CameraStreamMsg::update(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        RenderCamera* rc = dynamic_cast<RenderCamera*>(render_object);
        if (!rc) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly

        rc->update(rrc);
    }

    void CameraStreamMsg::render(RenderObject*& render_object, RenderContext* rc)
    {
        RenderCamera* camera = dynamic_cast<RenderCamera*>(render_object);
        if (!camera) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly

        //// get model matrix
        //Data* data = static_cast<Data*>(_data);
        //rmo->setModelMat(data->model_mat);

        camera->render(rc);
    }
}