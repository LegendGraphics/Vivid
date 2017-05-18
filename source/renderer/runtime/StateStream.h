#ifndef RENDERER_STATE_STREAM_H
#define RENDERER_STATE_STREAM_H

#include "renderer/resource/RenderObject.h"
#include "renderer/resource/RenderResource.h"
#include "renderer/resource/RenderMeshObject.h"
#include "math/Matrix.h"
#include "common/Component.h"

namespace te
{
    class RenderContext;
    class RenderResourceContext;


    //// data type communication between engine and renderer
    //enum class RenderObjectType
    //{
    //    MESH,
    //    TEXTURE,
    //    NOT_INITIALIZED
    //};

    /*struct StreamData
    {
        RenderObjectType type;
        void*            data;
    };*/

    // intermediate stream data between engine and renderer
    // remember the basic msg data unit is based on component
    /*class StreamData
    {
    private:
        using StreamDataMap = std::unordered_map<RenderObjectType, void*>;
    public:
        void feed(RenderObjectType type, void* data) { _data_map.insert({ type, data }); }
        void* get(RenderObjectType type) { return _data_map[type]; }
    private:
        StreamDataMap   _data_map;
    };*/

    class StreamMsg
    {
    public:
        enum MsgType
        {
            CREATE,
            UPDATE,
            RENDER,
            NOT_INITIALIZED
        };

    public:
        StreamMsg() : _data(nullptr), _msg_type(NOT_INITIALIZED), _handle(0xFFFFFFFF){};
        StreamMsg(MsgType type, Handle handle, void* data) : _data(data), _msg_type(type), _handle(handle){};
        virtual ~StreamMsg() {};

        void setMsgType(MsgType type) { _msg_type = type; }
        MsgType getMsgType() const { return _msg_type; }

        void setHandle(Handle handle) { _handle = handle; }
        Handle getHandle() const { return _handle; }

        void feedData(void* data) { _data = data; }
        void* getData() const { return _data; }

        virtual RenderObject* createRenderObject() { return nullptr; }

        virtual void process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc);
        

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc) = 0;
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc) = 0;
        virtual void render(RenderObject*& render_object, RenderContext* rc) = 0;

    protected:
        void*               _data;
        MsgType             _msg_type;
        Handle              _handle;
    };

    using StateStream = std::vector<StreamMsg*>;


    //// general node stream
    //class NodeStreamMsg : public StreamMsg
    //{
    //public:
    //    NodeStreamMsg();
    //    virtual ~NodeStreamMsg();

    //protected:
    //    virtual void create(RenderObject*& render_object, RenderResourceContext* rrc);
    //    virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
    //    virtual void render(RenderObject*& render_object, RenderContext* rc);
    //};


    //// camera data stream
    //class CameraStreamMsg : public StreamMsg
    //{
    //public:
    //    CameraStreamMsg();
    //    virtual ~CameraStreamMsg();

    //protected:
    //    virtual void create(RenderObject*& render_object, RenderResourceContext* rrc);
    //    virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
    //    virtual void render(RenderObject*& render_object, RenderContext* rc);
    //};


    // test a mesh stream msg
    class MeshStreamMsg : public StreamMsg
    {
    public:
        MeshStreamMsg(MsgType type, Handle handle, void* data);
        virtual ~MeshStreamMsg();

        virtual RenderObject* createRenderObject() { return new RenderMeshObject; }

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject*& render_object, RenderContext* rc);
    };

    /*class TextureStreamMsg : public StreamMsg
    {
    public:
        TextureStreamMsg();
        virtual ~TextureStreamMsg();

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject*& render_object, RenderContext* rc);
    };*/
}

#endif
