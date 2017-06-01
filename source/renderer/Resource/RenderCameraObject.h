#ifndef RENDERER_RENDER_CAMERA_OBJECT_H
#define RENDERER_RENDER_CAMERA_OBJECT_H

#include <unordered_map>
#include "base/Types.h"
#include "base/String.h"
#include "renderer/resource/RenderObject.h"

#include "common/Camera.h"

namespace te
{

    class RenderResourceContext;
    class RenderContext;
    class StreamMsg;

    class RenderCameraObject : public RenderObject
    {
    public:
        static RenderObject::Type TYPE;

        RenderCameraObject();
        ~RenderCameraObject();

        void create(RenderResourceContext* context);
        void update(RenderResourceContext* context);
        void render(RenderContext* context);

        void parseStreamMsg(StreamMsg* msg);

    private:
        void setCamera(RenderContext* context);

    private:
        GPUHandle       _camera_handle;
        Vector4         _view_port;
        Matrix          _proj_mat;
        Matrix          _view_mat;

    };
}

#endif
