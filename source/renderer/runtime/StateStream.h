#ifndef RENDERER_STATE_STREAM_H
#define RENDERER_STATE_STREAM_H

#include "renderer/resource/RenderMeshObject.h"
#include "renderer/resource/RenderShaderObject.h"

namespace te
{
    class RenderContext;
    class RenderResourceContext;
    class RenderWorld;

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
            UPDATE,     // update gpu object
            RENDER,     // set render status
            NOT_INITIALIZED
        };

    public:
        StreamMsg() : _data(nullptr), _msg_type(NOT_INITIALIZED) {};
        StreamMsg(MsgType type, void* data) : _data(data), _msg_type(type){};
        virtual ~StreamMsg() {};

        void setMsgType(MsgType type) { _msg_type = type; }
        MsgType getMsgType() const { return _msg_type; }

        void feedData(void* data) { _data = data; }
        void* getData() const { return _data; }

    protected:
        void*               _data;
        MsgType             _msg_type;
    };

    class ResourceStreamMsg : public StreamMsg
    {
    public:
        ResourceStreamMsg() : _handle(0xFFFFFFFF) {};
        ResourceStreamMsg(MsgType type, Handle handle, void* data) : StreamMsg(type, data), _handle(handle) {};
        virtual ~ResourceStreamMsg() {};

        Handle getHandle() const { return _handle; }

        virtual void setHandle(Handle handle) { _handle = handle; }

        virtual RenderObject* createRenderObject() { return nullptr; }

        virtual void process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc);
    protected:
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc) = 0;
        virtual void render(RenderObject*& render_object, RenderContext* rc) = 0;

    protected:
        Handle  _handle;
    };

    using ResourceStream = std::vector<ResourceStreamMsg*>;

    class RenderStreamMsg : public StreamMsg
    {
    public:
        RenderStreamMsg() {};
        RenderStreamMsg(MsgType type, void* data) : StreamMsg(type, data){};
        virtual ~RenderStreamMsg() {};

        virtual void process(RenderWorld* rw, RenderContext* rc, RenderResourceContext* rrc);
    protected:
        virtual void update(RenderWorld*& rw, RenderResourceContext* rrc) = 0;
        virtual void render(RenderWorld*& rw, RenderContext* rc) = 0;
    protected:
        ResourceStream  _resources;
    };

    using StateStream = std::vector<RenderStreamMsg*>;


    class NodeStreamMsg : public RenderStreamMsg
    {
    public:
        NodeStreamMsg(MsgType type, void* data);
        virtual ~NodeStreamMsg();

    protected:
        virtual void update(RenderWorld*& rw, RenderResourceContext* rrc);
        virtual void render(RenderWorld*& rw, RenderContext* rc);
        void setShaderUniforms(RenderContext* rc);
    protected:
        ShaderUniforms  _uniforms;

    };

    class CameraStreamMsg : public RenderStreamMsg
    {
    public:
        CameraStreamMsg(MsgType type, void* data);
        virtual ~CameraStreamMsg();

    protected:
        virtual void update(RenderWorld*& rw, RenderResourceContext* rrc);
        virtual void render(RenderWorld*& rw, RenderContext* rc);
        void setCameraState(RenderContext* rc);
    protected:
        
    };


    // test a mesh stream msg
    class MeshStreamMsg : public ResourceStreamMsg
    {
    public:
        MeshStreamMsg(MsgType type, Handle handle, void* data);
        virtual ~MeshStreamMsg();

        virtual void setHandle(Handle handle) 
        { 
            _handle = handle; 
            static_cast<Mesh*>(_data)->setROHandle(handle); 
        }
        virtual RenderObject* createRenderObject() { return new RenderMeshObject; }

    protected:
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject*& render_object, RenderContext* rc);
    };

    // test a shader stream msg
    class ShaderStreamMsg : public ResourceStreamMsg
    {
    public:
        ShaderStreamMsg(MsgType type, Handle handle, void* data);
        virtual ~ShaderStreamMsg();

        virtual void setHandle(Handle handle)
        {
            _handle = handle;
            static_cast<Shader*>(_data)->setROHandle(handle);
        }
        virtual RenderObject* createRenderObject() { return new RenderShaderObject; }

    protected:
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
