#ifndef RENDERER_STATE_STREAM_H
#define RENDERER_STATE_STREAM_H

#include "vivid/renderer/runtime/RenderMeshObject.h"
#include "vivid/renderer/runtime/RenderShaderObject.h"
#include "vivid/renderer/runtime/RenderTextureObject.h"


namespace vivid
{
    class RenderContext;
    class RenderResourceContext;
    class RenderWorld;

    namespace stream_message
    {
        enum ActionType
        {
            UPDATE,     // update resource
            RENDER,     // set render status
            NOT_INITIALIZED
        };
        enum DataType
        {
            // some render state for device
        };
    }

    class StateStreamMsg
    {
    public:
        StateStreamMsg() : _type(stream_message::NOT_INITIALIZED), _data(nullptr) {};
        StateStreamMsg(stream_message::ActionType type, void* data) : _type(type), _data(data) {};
        virtual ~StateStreamMsg() {};

        void feedData(void* data) { _data = data; }
        void* getData() const { return _data; }

        void setActionType(stream_message::ActionType type) { _type = type; }
        stream_message::ActionType getActionType() { return _type; }

        virtual void process(RenderContext* rc, RenderResourceContext* rrc, RenderWorld* rw) = 0;

    protected:
        void*                       _data;
        stream_message::ActionType  _type;
    };

    class ResourceStreamMsg : public StateStreamMsg
    {
    public:
        ResourceStreamMsg() {};
        ResourceStreamMsg(stream_message::ActionType type, Handle handle, void* data) : StateStreamMsg(type, data), _handle(handle) {};
        virtual ~ResourceStreamMsg() {};

        virtual Handle getHandle() const { return _handle; }
        virtual void setHandle(Handle handle) { _handle = handle; }
        // ownership of the object created here will be passed to RenderWorld 
        virtual RenderObject* createRenderObject() = 0;

        virtual void process(RenderContext* rc, RenderResourceContext* rrc, RenderWorld* rw);

    protected:
        virtual void update(RenderObject* render_object, RenderResourceContext* rrc) = 0;
        virtual void render(RenderObject* render_object, RenderContext* rc) = 0;

    protected:
        Handle _handle;
    };

    class DataStreamMsg : public StateStreamMsg
    {
    public:
        DataStreamMsg() {};
        DataStreamMsg(stream_message::DataType type, void* data) : StateStreamMsg(stream_message::UPDATE, data), _type(type) {};
        virtual ~DataStreamMsg() {};

        virtual void process(RenderContext* rc, RenderResourceContext* rrc, RenderWorld* rw);

    protected:
        stream_message::DataType        _type;
    };

    /*
    class StateStreamMsg
    {
    public:
        enum ActionType
        {
            UPDATE,     // update resource
            RENDER,     // set render status
            NOT_INITIALIZED
        };
    public:
        StateStreamMsg() : _data(nullptr), _type(NOT_INITIALIZED), _handle(0xFFFFFFFF) {};
        StateStreamMsg(ActionType type, Handle handle, void* data) : _type(type), _handle(handle), _data(data) {};
        virtual ~StateStreamMsg() {};

        virtual RenderObject* createRenderObject() { return nullptr; }

        Handle getHandle() const { return _handle; }
        virtual void setHandle(Handle handle) { _handle = handle; }

        void setActionType(ActionType type) { _type = type; }
        ActionType getActionType() { return _type; }

        void feedData(void* data) { _data = data; }
        void* getData() const { return _data; }

        virtual void process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc) = 0;

    protected:
        void*       _data;
        ActionType  _type;
        Handle      _handle;
    };
    */

    /*
    class ResourceStreamMsg : public StateStreamMsg
    {
    public:
        ResourceStreamMsg(){};
        ResourceStreamMsg(ActionType type, Handle handle, void* data) : StateStreamMsg(type, handle, data) {};
        virtual ~ResourceStreamMsg() {};

        virtual void process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc);

    protected:
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc) = 0;
        virtual void render(RenderObject*& render_object, RenderContext* rc) = 0;
    };
    */

    /*
    // Currently using Render as default action
    class DataStreamMsg : public StateStreamMsg
    {
    public:
        enum Type
        {
            // some render state for device
        };
    public:
        DataStreamMsg() {};
        DataStreamMsg(Type type, void* data) : StateStreamMsg(RENDER, 0, data), _type(type) {};
        virtual ~DataStreamMsg() { delete _object; };

        virtual RenderObject* createRenderObject()
        {
            _object = new RenderObject;
            return _object;
        }

        virtual void process(RenderObject*& render_object, RenderContext* rc, RenderResourceContext* rrc);
    protected:
        virtual void render(RenderObject*& render_object, RenderContext* rc) = 0;
    protected:
        Type                _type;
        RenderObject*       _object;
    };
    */

    using StateStream = std::vector<StateStreamMsg*>;


    /*class NodeStreamMsg : public RenderStreamMsg
    {
    public:
        NodeStreamMsg(MsgType type, void* data);
        virtual ~NodeStreamMsg();

    protected:
        virtual void update(RenderWorld*& rw, RenderResourceContext* rrc);
        virtual void render(RenderWorld*& rw, RenderContext* rc);
        void setShaderUniforms(RenderContext* rc);
        void setSpaceState(RenderContext* rc);
        void setCameraState(RenderContext* rc);
        void setDraw(RenderContext* rc);
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

    };*/


    // test a mesh stream msg
    class MeshStreamMsg : public ResourceStreamMsg
    {
    public:
        MeshStreamMsg(stream_message::ActionType type, Handle handle, void* data);
        virtual ~MeshStreamMsg();

        virtual void setHandle(Handle handle)
        {
            _handle = handle;
            static_cast<Mesh*>(_data)->setROHandle(handle);
        }
        virtual RenderObject* createRenderObject() { return new RenderMeshObject; }

    protected:
        virtual void update(RenderObject* render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject* render_object, RenderContext* rc);
    };

    // test a shader stream msg
    class ShaderStreamMsg : public ResourceStreamMsg
    {
    public:
        struct Data {
            Shader*     shader;
            Mesh*       mesh;
        };
    public:
        ShaderStreamMsg(stream_message::ActionType type, Handle handle, void* data);
        virtual ~ShaderStreamMsg();

        virtual void setHandle(Handle handle);
        virtual RenderObject* createRenderObject() { return new RenderShaderObject; }

    protected:
        virtual void update(RenderObject* render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject* render_object, RenderContext* rc);
    };

    class TextureStreamMsg : public ResourceStreamMsg
    {
    public:
        TextureStreamMsg(stream_message::ActionType type, Handle handle, void* data);
        virtual ~TextureStreamMsg();

        virtual void setHandle(Handle handle);
        virtual RenderObject* createRenderObject() { return new RenderTextureObject; }

    protected:
        virtual void update(RenderObject* render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject* render_object, RenderContext* rc);
    };
}

#endif
