#ifndef COMMON_UPLOADER_H
#define COMMON_UPLOADER_H

#include "vivid/common/Component.h"
#include "vivid/common/Material.h"
#include "vivid/common/Camera.h"
#include "vivid/common/SpaceState.h"
#include "vivid/renderer/runtime/StateStream.h"

namespace vivid
{
    class UploadToRender : public Render
    {
    public:
        UploadToRender();

        void setActionType(stream_message::ActionType type);

        void update();

    protected:
        virtual void assembleUpdateMsg();
        virtual void assembleRenderMsg();

        // build state stream msg
        void updateMesh();
        void updateTexture();
        void updateShader();

        void renderMesh();
        void renderTexture();
        void renderShader();

    protected:
        void fillShaderUniforms();
        void setCameraState(MaterialPtr mtl);
        void setSpaceState(MaterialPtr mtl);


        /* void uploadMaterial();
         void uploadCameraState();

     private:
         void setWorldPosition();*/

    private:
        class RenderInterface*              _renderer;
        stream_message::ActionType          _action_type;
    };
}

#endif // COMMON_UPLOADER_H


