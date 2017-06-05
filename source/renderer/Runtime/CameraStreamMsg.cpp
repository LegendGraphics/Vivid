#include "renderer/runtime/StateStream.h"


namespace te
{
    CameraStreamMsg::CameraStreamMsg(MsgType type, void* data)
        :NodeStreamMsg(type, data)
    {
    }

    CameraStreamMsg::~CameraStreamMsg()
    {
        /* delete static_cast<Data*>(_data);
         _data = nullptr;*/
    }

    void CameraStreamMsg::update(RenderWorld*& rw, RenderResourceContext* rrc)
    {
        
    }

    void CameraStreamMsg::render(RenderWorld*& rw, RenderContext* rc)
    {
        
    }
}