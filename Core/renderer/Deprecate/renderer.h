#ifndef RENDERER_RENDERER_H
#define RENDERER_RENDERER_H

#include "base/refptr.hpp"
#include "base/ref.h"
#include "renderer/gl_databuffer.h"
#include "renderer/gl_program.h"
#include "renderer/gl_texture.h"

class Scene;
class NodeVisitor;

class Renderer: public Ref
{
public:
    Renderer();
    virtual ~Renderer();

    void render(Scene* running_scene, NodeVisitor* node_visitor);

    inline GLProgram* getGLProgram() { return _gl_program.get(); }
    inline GLTexture* getGLTexture() { return _gl_texture.get(); }
    inline GLDataBuffer* getGLDataBuffer() { return _gl_databuffer.get(); }

    void initialize();

    void flush();

    void clear();
    
protected:
    bool _is_rendering;

    RefPtr<GLProgram> _gl_program;
    RefPtr<GLDataBuffer> _gl_databuffer;
    RefPtr<GLTexture> _gl_texture;
};

#endif // RENDERER_RENDERER_H
