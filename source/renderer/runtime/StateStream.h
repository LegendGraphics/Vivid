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

    // intermediate stream data between engine and renderer
    // remember the basic msg data unit is based on component
    class StreamData
    {
    private:
        using StreamDataMap = std::unordered_map<ComponentType, void*>;
    public:
        void feed(ComponentType type, void* data) { _data_map.insert({ type, data }); }
        void* get(ComponentType type) { return _data_map[type]; }
    private:
        StreamDataMap   _data_map;
    };

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
        StreamMsg() : _data(nullptr), _msg_type(NOT_INITIALIZED)/*, _handle(nullptr)*/ {};
        virtual ~StreamMsg() {};

        void setMsgType(MsgType type) { _msg_type = type; }
        MsgType getMsgType() const { return _msg_type; }

        /*void setNodeType(NodeType type) { _node_type = type; }
        NodeType getNodeType() const { return _node_type; }*/

        //void setHandle(Handle* handle) { _handle = handle; }
        //Handle* getHandle() { return _handle; }
        virtual void process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc);
        virtual void feedData(ComponentType type, void* data) { _data->feed(type, data); }

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc) = 0;
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc) = 0;
        virtual void render(RenderObject*& render_object, RenderContext* rc) = 0;

    protected:
        StreamData*        _data;        // store component data
        MsgType            _msg_type;
        //NodeType           _node_type;
        //Handle*       _handle;
    };


    // general node stream
    class NodeStreamMsg : public StreamMsg
    {
    public:
        NodeStreamMsg();
        virtual ~NodeStreamMsg();

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject*& render_object, RenderContext* rc);
    };


    using StateStream = std::vector<NodeStreamMsg*>;

    // camera data stream
    class CameraStreamMsg : public NodeStreamMsg
    {
    public:
        CameraStreamMsg();
        virtual ~CameraStreamMsg();

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject*& render_object, RenderContext* rc);
    };


    // test a mesh stream msg
    class MeshStreamMsg : public NodeStreamMsg
    {
    public:
        struct Data
        {
            RenderMeshObject*   rmo;
            Matrix              model_mat;
        };

    public:
        virtual ~MeshStreamMsg();

    protected:
        virtual void create(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject*& render_object, RenderContext* rc);
    };
}

#endif
