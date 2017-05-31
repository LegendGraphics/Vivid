#include "renderer/runtime/StateStream.h"


namespace te
{
    CameraStreamMsg::CameraStreamMsg(MsgType type, Handle handle, void* data)
        :StreamMsg(type, handle, data)
    {
    }

    CameraStreamMsg::~CameraStreamMsg()
    {
        /* delete static_cast<Data*>(_data);
         _data = nullptr;*/
    }

    void CameraStreamMsg::create(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        RenderCameraObject* rco = static_cast<RenderCameraObject*>(render_object);
        if (!rco) return;

        // do something if we want to update the status of rco
        // usually get the data in the message, parse it and set the rco accordingly
        rco->parseStreamMsg(this);

        // create resource context
        rco->create(rrc);

    }

    void CameraStreamMsg::update(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        RenderCameraObject* rco = static_cast<RenderCameraObject*>(render_object);
        if (!rco) return;

        // do something if we want to update the status of rco
        // usually get the data in the message, parse it and set the rco accordingly
        rco->parseStreamMsg(this);

        rco->update(rrc);
    }

    void CameraStreamMsg::render(RenderObject*& render_object, RenderContext* rc)
    {
        RenderCameraObject* rco = static_cast<RenderCameraObject*>(render_object);
        if (!rco) return;

        // do something if we want to update the status of rco
        // usually get the data in the message, parse it and set the rco accordingly

        //// get model matrix
        //Data* data = static_cast<Data*>(_data);
        //rco->setModelMat(data->model_mat);

        rco->render(rc);
    }
}