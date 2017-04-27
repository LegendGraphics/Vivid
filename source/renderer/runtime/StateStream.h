#ifndef RENDERER_STATESTREAM_H
#define RENDERER_STATESTREAM_H

#include "renderer/resource/RenderObject.h"
#include "renderer/resource/RenderResource.h"
#include "renderer/resource/RenderMeshObject.h"

namespace te
{
    class RenderContext;
    class RenderResourceContext;

    class StreamMsg
    {
    public:
        enum MsgType
        {
            CREATE,
            UPDATE,
            RENDER
        };

    public:
        StreamMsg() {};
        virtual ~StreamMsg() {};

        void setMsgType(MsgType type) { _type = type; }
        MsgType getMsgType() { return _type; }
        void setHandle(Handle* handle) { _handle = handle; }
        Handle* getHandle() { return _handle; }
        virtual void process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc);
        virtual void feedData(RenderObject*& render_object) = 0;

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc) = 0;
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc) = 0;
        virtual void render(RenderObject*& render_objcet, RenderContext* rc) = 0;

    protected:
        void*         _data;
        MsgType       _type;
        Handle*       _handle;
    };

    using StateStream = std::vector<StreamMsg*>;

    // test a mesh stream msg
    class MeshStreamMsg : public StreamMsg
    {
    protected:
        struct Data
        {
            RenderMeshObject* rmo;
        };

    public:
        virtual ~MeshStreamMsg();
        virtual void feedData(RenderObject*& render_object);

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject*& render_objcet, RenderContext* rc);
    };
}

#endif
