#include "common/Uploader.h"
#include "renderer/RenderInterface.h"
#include "common/Camera.h"
#include "common/SpaceState.h"
#include "common/MeshRender.h"

namespace te
{
    UploadToRender::UploadToRender()
    {
        // using default renderer
        _renderer = RenderInterface::getInstance();
    }

    // send plain old data to renderer
    void UploadToRender::update()
    {
        uploadSpaceStatus();
        uploadCameraStatus();
        uploadMeshRender();
    }

    void UploadToRender::uploadMeshRender()
    {
        if (hasComponent<MeshRender>())
        {

        }
    }

    void UploadToRender::uploadCameraStatus()
    {
        if (hasComponent<CameraState>())
        {
            /*CameraState* cs = getComponent<CameraState>();
            CameraStreamMsg* csm = new CameraStreamMsg;
            csm->setMsgType(StreamMsg::CREATE);
            csm->setHandle(mesh->getRenderObjectHandle());
            CameraStreamMsg::Data* data = new CameraStreamMsg::Data;
            data->rmo = new RenderMeshObject(mesh);
            csm->feedData(data);
            _stream.push_back(csm);*/
        }
    }

    void UploadToRender::uploadSpaceStatus()
    {
        if (hasComponent<SpaceState>())
        {

        }
    }
}