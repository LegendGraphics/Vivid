//#include "renderer/runtime/StateStream.h"
//
//
//namespace te
//{
//    TextureStreamMsg::TextureStreamMsg(ActionType type, Handle handle, void* data)
//        :ResourceStreamMsg(type, handle, data)
//    {
//    }
//
//    TextureStreamMsg::~TextureStreamMsg()
//    {
//    }
//
//    void TextureStreamMsg::update(RenderObject*& render_object, RenderResourceContext* rrc)
//    {
//        RenderTextureObject* rso = static_cast<RenderTextureObject*>(render_object);
//        if (!rso) return;
//
//        // do something if we want to update the status of rmo
//        // usually get the data in the message, parse it and set the rmo accordingly
//        rso->parseStreamMsg(this);
//
//        rso->update(rrc);
//    }
//
//    void TextureStreamMsg::render(RenderObject*& render_object, RenderContext* rc)
//    {
//        RenderTextureObject* rso = static_cast<RenderTextureObject*>(render_object);
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