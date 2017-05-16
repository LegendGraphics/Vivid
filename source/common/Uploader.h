#ifndef COMMON_UPLOADER_H
#define COMMON_UPLOADER_H

#include "common/Component.h"

namespace te
{
    class NodeStreamMsg;

    class UploadToRender : public Behavior
    {
    public:
        UploadToRender();

        void update();

    private:
        void uploadMeshRender(NodeStreamMsg* msg);
        void uploadCameraStatus(NodeStreamMsg* msg);
        void uploadSpaceStatus(NodeStreamMsg* msg);

        void initStreamMsg(NodeStreamMsg* msg);

    private:
        class RenderInterface*    _renderer;
    };
}

#endif // COMMON_UPLOADER_H


