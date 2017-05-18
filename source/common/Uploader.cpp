#include "common/Uploader.h"
#include "common/Camera.h"
#include "common/SpaceState.h"
#include "common/MeshRender.h"
#include "renderer/RenderInterface.h"
#include "renderer/runtime/StateStream.h"

namespace te
{
    UploadToRender::UploadToRender()
        :Render(ComponentType::UPLOAD_TO_RENDER)
    {
        // using default renderer
        _renderer = RenderInterface::getInstance();
    }

    void UploadToRender::setMsgType(StreamMsg::MsgType type)
    {
        _msg_type = type;
    }


    // send data to renderer
    void UploadToRender::update()
    {
        // feed data into msg
        uploadMesh();
        uploadTexture();
        uploadPosition();
    }

    void UploadToRender::uploadMesh()
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            MeshStreamMsg* msg = new MeshStreamMsg(_msg_type,
                mr->getMesh()->getROHandle(), 
                mr->getMesh().get());
            _renderer->_stream.push_back(msg);
        }
    }
    void UploadToRender::uploadTexture()
    {
        if (hasComponent<MeshRender>())
        {
            /*TextureStreamMsg* msg = new TextureStreamMsg;
            MeshRender* mr = getComponent<MeshRender>();
            msg->feedData(mr->getMesh().get());
            _renderer->_stream.push_back(msg);*/
        }
    }
    void UploadToRender::uploadPosition()
    {
        if (hasComponent<SpaceState>())
        {
            SpaceState* ss = getComponent<SpaceState>();
            /*msg->feedData(ComponentType::SPACE_STATE, ss);
            _renderer->_stream.push_back(msg); */
        }
    }
}