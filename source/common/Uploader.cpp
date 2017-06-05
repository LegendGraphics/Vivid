#include "common/Uploader.h"
#include "common/Camera.h"
#include "common/SpaceState.h"
#include "common/MeshRender.h"
#include "renderer/RenderInterface.h"

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
        RenderStreamMsg* msg = _owner->createStreamMsg(_msg_type);
        _renderer->_stream.push_back(msg);
    }

    void UploadToRender::assembleResourceMsg(ResourceStream& resource_stream)
    {
        uploadMesh(resource_stream);
        uploadTexture(resource_stream);
        uploadShader(resource_stream);
    }

    void UploadToRender::uploadMesh(ResourceStream& resource_stream)
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            MeshStreamMsg* msg = new MeshStreamMsg(_msg_type,
                mr->getMesh()->getROHandle(), 
                mr->getMesh().get());
            resource_stream.push_back(msg);
        }
    }

    void UploadToRender::uploadTexture(ResourceStream& resource_stream)
    {
        if (hasComponent<MeshRender>())
        {
            /*TextureStreamMsg* msg = new TextureStreamMsg;
            MeshRender* mr = getComponent<MeshRender>();
            msg->feedData(mr->getMesh().get());
            _renderer->_stream.push_back(msg);*/
        }
    }

    void UploadToRender::uploadShader(ResourceStream& resource_stream)
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            ShaderStreamMsg* msg = new ShaderStreamMsg(_msg_type,
                mr->getMaterial()->getShader()->getROHandle(),
                mr->getMaterial()->getShader().get());
            resource_stream.push_back(msg);
        }
    }

    Material::UniformValueMap& UploadToRender::getUniformValueMap()
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            return mr->getMaterial()->getUniformValueMap();
        }
    }

    CameraState& UploadToRender::getCameraState()
    {
        if (hasComponent<CameraState>())
        {
            CameraState* cs = getComponent<CameraState>();
            return *cs;
        }
    }



    /*void UploadToRender::uploadMaterial()
    {
        setWorldPosition();

        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            MaterialStreamMsg* msg = new MaterialStreamMsg(_msg_type,
                mr->getMaterial()->getROHandle(),
                mr->getMaterial().get());
            _renderer->_stream.push_back(msg);
        }
    }*/
    //void UploadToRender::uploadPosition()
    //{
    //    if (hasComponent<SpaceState>())
    //    {
    //        SpaceState* ss = getComponent<SpaceState>();
    //        /*msg->feedData(ComponentType::SPACE_STATE, ss);
    //        _renderer->_stream.push_back(msg); */
    //    }
    //}

    /*void UploadToRender::uploadCameraState()
    {
        if (hasComponent<CameraState>())
        {
            CameraState* cs = getComponent<CameraState>();
            CameraStreamMsg* msg = new CameraStreamMsg(_msg_type,
                dynamic_cast<Camera*>(_owner)->getROHandle(),
                dynamic_cast<Camera*>(_owner));
            _renderer->_stream.push_back(msg);
        }
    }


    void UploadToRender::setWorldPosition()
    {
        if (hasComponent<SpaceState>() && hasComponent<MeshRender>())
        {
            SpaceState* ss = getComponent<SpaceState>();
            Vector3 pos = ss->getLocalPosition();
            MeshRender* mr = getComponent<MeshRender>();
            mr->getMaterial()->setMatrix("worldMat", Matrix::translate(pos.x, pos.y, pos.z));
        }
    }*/


}