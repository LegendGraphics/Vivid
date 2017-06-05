#ifndef COMMON_UPLOADER_H
#define COMMON_UPLOADER_H

#include "common/Component.h"
#include "renderer/runtime/StateStream.h"

namespace te
{
    class UploadToRender : public Render
    {
    public:
        UploadToRender();

        void setMsgType(StreamMsg::MsgType type);

        void update();

        void assembleResourceMsg(ResourceStream& resource_stream);

    private:

        void uploadMesh(ResourceStream& resource_stream);
        void uploadTexture(ResourceStream& resource_stream);
        void uploadShader(ResourceStream& resource_stream);
        /* void uploadMaterial();
         void uploadCameraState();

     private:
         void setWorldPosition();*/

    private:
        class RenderInterface*    _renderer;
        StreamMsg::MsgType        _msg_type;
    };
}

#endif // COMMON_UPLOADER_H


