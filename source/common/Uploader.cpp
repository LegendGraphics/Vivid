#include "common/Uploader.h"
#include "base/Director.h"
#include "common/Scene.h"
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

    void UploadToRender::setActionType(stream_message::ActionType type)
    {
        _action_type = type;
    }

    // send data to renderer
    void UploadToRender::update()
    {
        if (_action_type == stream_message::UPDATE)
            assembleUpdateMsg();
        else if (_action_type == stream_message::RENDER)
            assembleRenderMsg();
    }

    void UploadToRender::assembleUpdateMsg()
    {
        updateMesh();
        updateShader();
    }

    void UploadToRender::assembleRenderMsg()
    {
        renderMesh();
        renderShader();
    }

    void UploadToRender::updateMesh()
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            MeshStreamMsg* msg = new MeshStreamMsg(stream_message::UPDATE,
                mr->getMesh()->getROHandle(), 
                mr->getMesh().get());
            _renderer->_stream.push_back(msg);
        }
    }

    void UploadToRender::updateTexture()
    {
        if (hasComponent<MeshRender>())
        {
            /*TextureStreamMsg* msg = new TextureStreamMsg;
            MeshRender* mr = getComponent<MeshRender>();
            msg->feedData(mr->getMesh().get());
            _renderer->_stream.push_back(msg);*/
        }
    }

    void UploadToRender::updateShader()
    {
        fillShaderUniforms();

        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            ShaderStreamMsg* msg = new ShaderStreamMsg(stream_message::UPDATE,
                mr->getMaterial()->getShader()->getROHandle(),
                mr->getMaterial()->getShader().get());
            _renderer->_stream.push_back(msg);
        }
    }

    void UploadToRender::renderMesh()
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            MeshStreamMsg* msg = new MeshStreamMsg(stream_message::RENDER,
                mr->getMesh()->getROHandle(),
                nullptr);
            _renderer->_stream.push_back(msg);
        }
    }

    void UploadToRender::renderTexture()
    {
        if (hasComponent<MeshRender>())
        {
            /*TextureStreamMsg* msg = new TextureStreamMsg;
            MeshRender* mr = getComponent<MeshRender>();
            msg->feedData(mr->getMesh().get());
            _renderer->_stream.push_back(msg);*/
        }
    }

    void UploadToRender::renderShader()
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            ShaderStreamMsg* msg = new ShaderStreamMsg(stream_message::RENDER,
                mr->getMaterial()->getShader()->getROHandle(),
                nullptr);
            _renderer->_stream.push_back(msg);
        }
    }

    void UploadToRender::fillShaderUniforms()
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            MaterialPtr mtl = mr->getMaterial();
            setSpaceState(mtl);
            setCameraState(mtl);
            mtl->setShaderUniforms();
        }
    }

    void UploadToRender::setCameraState(MaterialPtr mtl)
    {
        Camera* camera = Director::getInstance()->getActiveScene()->getActiveCamera();
        CameraState* cs = camera->getComponent<CameraState>();
        mtl->setMatrix("projMat", cs->getProjectTransform().rawMatrix());
        mtl->setMatrix("viewMat", cs->getViewTransform().rawMatrix());
    }

    void UploadToRender::setSpaceState(MaterialPtr mtl)
    {
        if (hasComponent<SpaceState>())
        {
            SpaceState* ss = getComponent<SpaceState>();
            mtl->setMatrix("worldMat", ss->getSpaceTransform().rawMatrix());
        }
    }

    /*ShaderUniforms UploadToRender::getShaderUniforms()
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            return mr->getMaterial()->getShaderUniformsByMap();
        }
    }*/

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