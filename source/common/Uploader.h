#ifndef COMMON_UPLOADER_H
#define COMMON_UPLOADER_H

#include "common/Component.h"

namespace te
{
    class UploadToRender : public Behavior
    {
    public:
        UploadToRender();

        void update();

    private:
        void uploadMeshRender();
        void uploadCameraStatus();
        void uploadSpaceStatus();

    private:
        class RenderInterface*    _renderer;
    };
}

#endif // COMMON_UPLOADER_H


