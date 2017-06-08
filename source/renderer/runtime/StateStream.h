#ifndef RENDERER_STATE_STREAM_H
#define RENDERER_STATE_STREAM_H

#include "renderer/resource/RenderMeshObject.h"
#include "renderer/resource/RenderShaderObject.h"
#include "renderer/resource/RenderTextureObject.h"


namespace te
{
    class RenderContext;
    class RenderResourceContext;

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
        MeshStreamMsg(ActionType type, Handle handle, void* data);
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
        ShaderStreamMsg(ActionType type, Handle handle, void* data);
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

    class TextureStreamMsg : public ResourceStreamMsg
    {
        TextureStreamMsg(ActionType type, Handle handle, void* data);
        virtual ~TextureStreamMsg();

        virtual void setHandle(Handle handle)
        {
            _handle = handle;
            static_cast<Texture*>(_data)->setROHandle(handle);
        }
        virtual RenderObject* createRenderObject() { return new RenderTextureObject; }

    protected:
        virtual void update(RenderObject*& render_object, RenderResourceContext* rrc);
        virtual void render(RenderObject*& render_object, RenderContext* rc);
    };
}

#endif
