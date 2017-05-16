#include "common/Uploader.h"
#include "common/Camera.h"
#include "common/SpaceState.h"
#include "common/MeshRender.h"
#include "renderer/RenderInterface.h"
#include "renderer/runtime/StateStream.h"

namespace te
{
    UploadToRender::UploadToRender()
    {
        // using default renderer
        _renderer = RenderInterface::getInstance();
    }

    void UploadToRender::initStreamMsg(NodeStreamMsg* msg)
    {
        if (getOwnerType() == NodeType::NODE)
            msg = new NodeStreamMsg;
        else if (getOwnerType() == NodeType::CAMERA)
            msg = new CameraStreamMsg;
    }

    // send data to renderer
    // component as basic unit
    void UploadToRender::update()
    {
        NodeStreamMsg* msg = nullptr;
        initStreamMsg(msg);

        msg->setMsgType(NodeStreamMsg::UPDATE);

        // feed data into msg
        uploadSpaceStatus(msg);
        uploadCameraStatus(msg);
        uploadMeshRender(msg);

        _renderer->_stream.push_back(msg);
    }

    void UploadToRender::uploadMeshRender(NodeStreamMsg* msg)
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            msg->feedData(ComponentType::MESH_RENDER, mr);
        }
    }

    void UploadToRender::uploadCameraStatus(NodeStreamMsg* msg)
    {
        if (hasComponent<CameraState>())
        {
            CameraState* cs = getComponent<CameraState>();
            msg->feedData(ComponentType::CAMERA_STATUS, cs);
        }
    }

    void UploadToRender::uploadSpaceStatus(NodeStreamMsg* msg)
    {
        if (hasComponent<SpaceState>())
        {
            SpaceState* ss = getComponent<SpaceState>();
            msg->feedData(ComponentType::SPACE_STATUS, ss);
        }
    }
}