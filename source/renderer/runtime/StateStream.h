#ifndef RENDERER_STATESTREAM_H
#define RENDERER_STATESTREAM_H

#include "renderer/resource/RenderObject.h"

namespace te
{
    class StreamMsg
    {
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
        virtual void process(RenderObject* render_object);

    protected:
        virtual void create(RenderObject* render_object) = 0;
        virtual void update(RenderObject* render_object) = 0;
        virtual void render(RenderObject* render_objcet) = 0;

    protected:
        void*         _data;
        MsgType       _type;
    };

    // test a mesh stream msg
    class MeshStreamMsg : public StreamMsg
    {
    protected:
        virtual void create(RenderObject* render_object);
        virtual void update(RenderObject* render_object);
        virtual void render(RenderObject* render_objcet);
    };
}

#endif
