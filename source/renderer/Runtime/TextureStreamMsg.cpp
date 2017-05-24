//#include "renderer/runtime/StateStream.h"
//
//
//namespace te
//{
//    ShaderStreamMsg::ShaderStreamMsg(MsgType type, Handle handle, void* data)
//        :StreamMsg(type, handle, data)
//    {
//    }
//
//    ShaderStreamMsg::~ShaderStreamMsg()
//    {
//        /* delete static_cast<Data*>(_data);
//         _data = nullptr;*/
//    }
//
//    void ShaderStreamMsg::create(RenderObject*& render_object, RenderResourceContext* rrc)
//    {
//        RenderShaderObject* rso = static_cast<RenderShaderObject*>(render_object);
//        if (!rso) return;
//
//        // do something if we want to update the status of rmo
//        // usually get the data in the message, parse it and set the rmo accordingly
//        rso->parseStreamMsg(this);
//
//        // create resource context
//        rso->create(rrc);
//
//    }
//
//    void ShaderStreamMsg::update(RenderObject*& render_object, RenderResourceContext* rrc)
//    {
//        RenderShaderObject* rso = static_cast<RenderShaderObject*>(render_object);
//        if (!rso) return;
//
//        // do something if we want to update the status of rmo
//        // usually get the data in the message, parse it and set the rmo accordingly
//        rso->parseStreamMsg(this);
//
//        rso->update(rrc);
//    }
//
//    void ShaderStreamMsg::render(RenderObject*& render_object, RenderContext* rc)
//    {
//        RenderShaderObject* rso = static_cast<RenderShaderObject*>(render_object);
//        if (!rso) return;
//
//        // do something if we want to update the status of rmo
//        // usually get the data in the message, parse it and set the rmo accordingly
//
//        //// get model matrix
//        //Data* data = static_cast<Data*>(_data);
//        //rmo->setModelMat(data->model_mat);
//
//        rso->render(rc);
//    }
//}