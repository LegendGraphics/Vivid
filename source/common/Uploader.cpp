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
        updateTexture();
        updateShader();
    }

    void UploadToRender::assembleRenderMsg()
    {
        renderMesh();
        renderTexture();
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
            auto aa = mr->getMesh()->getLayoutType();
            int a = aa;
        }
    }

    void UploadToRender::updateTexture()
    {
        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            std::vector<TexturePtr> textures = mr->getMaterial()->getTextures();
            for (TexturePtr texture : textures)
            {
                TextureStreamMsg::Data* msg_data = new TextureStreamMsg::Data;
                msg_data->texture = texture.get();
                TextureStreamMsg* msg = new TextureStreamMsg(stream_message::UPDATE,
                    texture->getROHandle(),
                    msg_data);
                _renderer->_stream.push_back(msg);
            }
        }
    }

    void UploadToRender::updateShader()
    {
        fillShaderUniforms();

        if (hasComponent<MeshRender>())
        {
            MeshRender* mr = getComponent<MeshRender>();
            ShaderStreamMsg::Data* msg_data = new ShaderStreamMsg::Data;
            msg_data->shader = mr->getMaterial()->getShader().get();
            msg_data->mesh = mr->getMesh().get();
            ShaderStreamMsg* msg = new ShaderStreamMsg(stream_message::UPDATE,
                mr->getMaterial()->getShader()->getROHandle(),
                msg_data);
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
            MeshRender* mr = getComponent<MeshRender>();
            std::vector<TexturePtr> textures = mr->getMaterial()->getTextures();
            ShaderPtr shader = mr->getMaterial()->getShader();
            for (TexturePtr texture : textures)
            {
                TextureStreamMsg::Data* msg_data = new TextureStreamMsg::Data;
                msg_data->texture = texture.get();
                msg_data->shader = shader.get();
                TextureStreamMsg* msg = new TextureStreamMsg(stream_message::RENDER,
                    texture->getROHandle(),
                    msg_data);
                _renderer->_stream.push_back(msg);
            }
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
            setCameraState(mtl); // TODO: this should be moved out to a separate DataStreamMsg
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