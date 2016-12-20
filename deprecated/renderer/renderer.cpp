#include <gl/glew.h>

#include "renderer/renderer.h"
#include "common/scene.h"
#include "common/node_visitor.h"

Renderer::Renderer()
:_is_rendering(false),
_gl_program(new GLProgram),
_gl_databuffer(new GLDataBuffer),
_gl_texture(new GLTexture)
{
}

Renderer::~Renderer()
{

}

void Renderer::render(Scene* active_scene, NodeVisitor* node_visitor)
{
    _is_rendering = true;
    
    node_visitor->attachRenderer(this);
    active_scene->traversal(node_visitor);

    glFlush();

    _is_rendering = false;
}

void Renderer::initialize()
{
    
}

void Renderer::clear()
{
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::flush()
{

}