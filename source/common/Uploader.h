#ifndef COMMON_UPLOADER_H
#define COMMON_UPLOADER_H

#include "common/Component.h"
#include "renderer/runtime/StateStream.h"

namespace te
{
    class UploadToRender : public Behavior
    {
    public:
        UploadToRender(StreamMsg::MsgType type);

        void update();

    private:
        void uploadMesh();
        void uploadTexture();
        void uploadPosition();

    private:
        class RenderInterface*    _renderer;
        StreamMsg::MsgType        _type;
    };
}

#endif // COMMON_UPLOADER_H


