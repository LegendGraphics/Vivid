#ifndef RENDERER_RENDERDEVICE_H
#define RENDERER_RENDERDEVICE_H

#include "base\Globals.h"
#include "base\Assert.h"

#include "renderer/resource/ShaderObject.h"
#include "renderer/Resource/Texture.h"
#include "renderer/Resource/VertexLayout.h"

namespace te
{
    class RenderContext;
    class RenderResourceContext;

    // render device objects
    template<class T> class RDObjects
    {
    public:
        uint32 add(const T& obj)
        {
            if (!_freeList.empty())
            {
                uint32 index = _freeList.back();
                _freeList.pop_back();
                _objects[index] = obj;
                return index + 1; // object handle Id starts from 1
            }
            else
            {
                _objects.push_back(obj);
                return (uint32)_objects.size();
            }
        }

        void remove(uint32 handle)
        {
            TE_ASSERT(handle > 0 && handle <= _objects.size(), "Invalid handle!");

            _objects[handle - 1] = T(); // replace with defualt object
            _freeList.push_back(handle - 1);
        }

        T& getRef(uint32 handle)
        {
            TE_ASSERT(handle > 0 && handle <= _objects.size(), "Invalid handle!");

            return _objects[handle - 1];
        }

        friend class RenderDevice;

    private:
        std::vector<T>      _objects;
        std::vector<uint32> _freeList;
    };

    class RenderDevice
    {
    public:
        RenderDevice();
        virtual ~RenderDevice();

        virtual bool open() = 0;
        virtual void close() = 0;

        virtual RenderContext* newContext();
        virtual void releaseContext(RenderContext* context);
        // RenderDevice will be called in the render thread loop and dispatch the 
        // commands to RenderContext, RenderContext will call actual Graphic API
        virtual void dispatch(RenderContext* context_) = 0;
        virtual void dispatch(RenderResourceContext* context_) = 0;

    private:
        typedef std::vector<RenderContext*> RenderContexts;
        RenderContexts _render_contexts;
    };

    //------ notes: -------
    // in Horde3D, there are RenderDevice and Renderer
    // RenderDevice holds vector of buffer/textures/render buffer/shaders(all are platform specific I think) 
    // and some other auxiliary things
    // Renderer is the interface to do rendering with the game world, in its render() function, it iterate the 
    // pile line commands and for draw geometry command, it iterate all renderable objects
    // in each renderable objects, it will call RenderDevice to do actual work (bind buffer, shader, set uniforms
    // and finally drawIndex or drawElement like in OpenGL), render function for each type also defined in Renderer
    // ------------------------------------------------------
    // in Stingray, there are RenderDevice, RenderWorld and RenderInterface
    // RenderDevice should be similar to RenderDevice in Horde3D except that it's an abstract class and each platform
    // will have its own XXXRenderDevice
    // RenderInterface receive render message from the main engine and send it to RenderWorld to do the render
    // I think RenderInterface is not very necessary for current stage (my sense is that this 
    // design is to separate the render thread from the main thread)
    // So I will mimic RenderWorld as the Renderer in Horde3D in my next implementation.
    //
    // One important thing I borrow from Stingray is that we decouple the render operation (for renderable objects)
    // from platform specific operation while in Horde3D it's binded to OpenGL API. So in render function for each
    // type, I will generate a stream which contains a series of sequential abstract operation on device. Then the stream
    // is sent to XXXRenderDevice and translated into platform specific operations.

    // TODO: there should be a resource manager and all resource can be accessed by id (uint32)
}

#endif
