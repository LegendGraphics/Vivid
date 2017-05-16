#include "renderer/runtime/StateStream.h"
#include "renderer/runtime/RenderNodeObject.h"

namespace te
{
    NodeStreamMsg::NodeStreamMsg()
    {
    }

    NodeStreamMsg::~NodeStreamMsg()
    {
        /*delete static_cast<Data*>(_data);
        _data = nullptr;*/
    }

    void NodeStreamMsg::create(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        //if (render_object)
        //{
        //    delete static_cast<Data*>(_data)->rmo;
        //    return;
        //}
        //render_object = static_cast<Data*>(_data)->rmo; // pass the ownership to RenderWorld
    }

    void NodeStreamMsg::update(RenderObject*& render_object, RenderResourceContext* rrc)
    {
        RenderNodeObject* node = dynamic_cast<RenderNodeObject*>(render_object);
        if (!node) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly

        node->update(rrc);
    }

    void NodeStreamMsg::render(RenderObject*& render_object, RenderContext* rc)
    {
        RenderNodeObject* node = dynamic_cast<RenderNodeObject*>(render_object);
        if (!node) return;

        // do something if we want to update the status of rmo
        // usually get the data in the message, parse it and set the rmo accordingly

        //// get model matrix
        //Data* data = static_cast<Data*>(_data);
        //rmo->setModelMat(data->model_mat);

        node->render(rc);
    }
}