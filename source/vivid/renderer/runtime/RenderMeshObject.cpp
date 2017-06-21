#include "vivid/renderer/runtime/RenderMeshObject.h"

#include "vivid/renderer/device/RenderContext.h"
#include "vivid/renderer/device/RenderDevice.h"
#include "vivid/renderer/runtime/RenderCamera.h"
#include "vivid/renderer/resource/RenderResourceContext.h"
#include "vivid/renderer/resource/ResourceStream.h"
#include "vivid/renderer/runtime/StateStream.h"

namespace vivid
{
    RenderObject::Type RenderMeshObject::TYPE = RenderObject::NOT_INITIALIZED;

    RenderMeshObject::RenderMeshObject()
        : RenderObject(TYPE),
        _index_buffer(0xFFFFFFFF),
        _vertex_buffer(0xFFFFFFFF),
        _vao(0xFFFFFFFF)
    {
    }

    RenderMeshObject::~RenderMeshObject()
    {
    }


    void RenderMeshObject::update(RenderResourceContext* context)
    {
        if (0xFFFFFFFF == _vao)
            allocMeshResource(context);
    }

    void RenderMeshObject::render(RenderContext* context)
    {
        // set index buffer
        //RenderContext::IndexCmdStream* ics = new RenderContext::IndexCmdStream;
        //ics->bufHandle = _indexBuf;
        //ics->idxFormat = IndexFormat::IDXFMT_32;
        //RenderContext::Command setIndexBuffer = { 0, (void*)ics, RenderContext::CommandType::UPDATE_INDEX_BUFFER };
        //context->commands().push_back(setIndexBuffer);

        // set vertex buffer
        command_stream::VertexCmdStream* vcs = new command_stream::VertexCmdStream;
        vcs->vao_handle = _vao;
        vcs->base_index = 0;
        vcs->base_vertex = 0;
        vcs->num_indices = _num_indices;
        RenderContext::Command setVertexBuffer = { 0, (void*)vcs, command_stream::CommandType::UPDATE_VERTEX_BUFFER };
        context->commands().push_back(setVertexBuffer);

        //bool useDebug = true;
        //if (useDebug)
        //{
        //    RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;
        //    scs->shader_handle = 0xFFFFFFFF; // use it to indicate the default shader in device

        //    ShaderVariable model_mat_var;
        //    model_mat_var.klass = shader_data::MATRIX4X4;
        //    model_mat_var.elements = 1;
        //    model_mat_var.offset = 0;
        //    model_mat_var.element_stride = 0;
        //    model_mat_var.semantic_name = "worldMat";
        //    scs->variables.push_back(model_mat_var);

        //    char* data_ptr = new char[4 * 4 * 4]; // for a float 4*4 matrix
        //    memcpy(data_ptr, &_model_mat(0, 0), 4 * 4 * 4);
        //    scs->data = (void*)data_ptr;

        //    RenderContext::Command setShaderObject = { 0,  (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
        //    context->commands().push_back(setShaderObject);
        //}
        //else
        //{
        //    RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;
        //    scs->shader_handle = _shader_object->render_resource_handle;
        //    // set data
        //    // set variable
        //    RenderContext::Command setShaderObject = { 0, (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
        //    context->commands().push_back(setShaderObject);
        //}

        

    }

    void RenderMeshObject::parseStreamMsg(StateStreamMsg* msg)
    {
        Mesh* mesh = static_cast<Mesh*>(msg->getData());

        _index_array = &mesh->getTriangles();
        _vertex_array = &mesh->getVertices();
        _layout_type = mesh->getLayoutType();
        _num_indices = (*_index_array).size();
    }


    void RenderMeshObject::allocMeshResource(RenderResourceContext * context)
    {
        allocIndexBuffer(context);
        allocVertexBuffer(context);
        allocVertexDeclaration(context);
    }

    void RenderMeshObject::allocIndexBuffer(RenderResourceContext * context)
    {
        resource_stream::IndexStream* is = new resource_stream::IndexStream;
        is->res = &_index_buffer;
        is->size = 4 * (*_index_array).size();
        is->raw_data = &(*_index_array)[0];

        RenderResourceContext::Message allc_is = {
            resource_stream::MessageType::ALLOC_INDEX_BUFFER, (void*)is };
        context->messages().push_back(allc_is);
    }

    void RenderMeshObject::allocVertexBuffer(RenderResourceContext * context)
    {
        resource_stream::VertexStream* vs = new resource_stream::VertexStream;
        vs->res = &_vertex_buffer;
        vs->size = (*_vertex_array).sizeInBytes();//4 * m->getVertices().size(); // 12 float for each vertex(PNTB)
        vs->stride = (*_vertex_array).sizeInBytes() / (*_vertex_array).size();
        vs->raw_data = (*_vertex_array).buffer(); // assume memory in std::vector<Vertex_PNTB> is tight packed
                                                  //float* aa = &m->getVertices()[0];

        RenderResourceContext::Message allc_vs = {
            resource_stream::MessageType::ALLOC_VERTEX_BUFFER, (void*)vs };
        context->messages().push_back(allc_vs);
    }

    void RenderMeshObject::allocVertexDeclaration(RenderResourceContext * context)
    {
        resource_stream::VertexDeclarationStream* vds = new resource_stream::VertexDeclarationStream;
        vds->res = &_vao;
        vds->layout_type = _layout_type;

        vds->index_buffer = &_index_buffer;
        vds->vertex_buffers.push_back(&_vertex_buffer);

        RenderResourceContext::Message allc_vd = {
            resource_stream::MessageType::ALLOC_VERTEX_DECLARATVIVID_ION, (void*)vds };
        context->messages().push_back(allc_vd);
    }

    void RenderMeshObject::setVertexContext(RenderContext* context)
    {
        command_stream::VertexCmdStream* vcs = new command_stream::VertexCmdStream;
        vcs->vao_handle = _vao;
        vcs->base_index = 0;
        vcs->base_vertex = 0;
        vcs->num_indices = _num_indices;
        RenderContext::Command set_vertex_buffer = { 0, (void*)vcs, command_stream::CommandType::UPDATE_VERTEX_BUFFER };
        context->commands().push_back(set_vertex_buffer);
    }



    //void RenderMeshObject::render(RenderContext* context)
    //{
    //    // set index buffer
    //    //RenderContext::IndexCmdStream* ics = new RenderContext::IndexCmdStream;
    //    //ics->bufHandle = _indexBuf;
    //    //ics->idxFormat = IndexFormat::IDXFMT_32;
    //    //RenderContext::Command setIndexBuffer = { 0, (void*)ics, RenderContext::CommandType::UPDATE_INDEX_BUFFER };
    //    //context->commands().push_back(setIndexBuffer);

    //    // set vertex buffer
    //    RenderContext::VertexCmdStream* vcs = new RenderContext::VertexCmdStream;
    //    vcs->vao_handle = _vao;
    //    vcs->base_index = 0;
    //    vcs->base_vertex = 0;
    //    vcs->num_indices = _num_indices;
    //    RenderContext::Command setVertexBuffer = { 0, (void*)vcs, RenderContext::CommandType::UPDATE_VERTEX_BUFFER };
    //    context->commands().push_back(setVertexBuffer);

    //    // prepare for shader object
    //    // Lin 1/19/2017
    //    // Two ways here, (choose #2 in current dev stage)
    //    // Shader require different constants (uniform in GLSL) set before rendering
    //    // 1. set the constants here (I think to prevent too much memory copy, we need to use handle)
    //    // 2. only set the shader and let shader get all constants it needed ready in XXXRenderDevice
    //    //    - still need a way to let shader get the constants it needed.
    //    //    - constants usually stores in Material resource
    //    //    - in Horde3D, the lowest level of shader structure is ShaderCombination which is kept as a 
    //    //      std::vector<>in ShaderContext. ShaderContext is also kept as a std::vector<> in ShaderResource.
    //    //      Each ShaderContext seems related to different effect pass (ShadowMap, Light, Ambient, AttribPass, etc)
    //    //      Since there are multiple shaders in one ShaderContext, client use a mask (uint) to decide which
    //    //      shader to use.
    //    //
    //    // Perhaps we should separate custom uniforms from general uniforms (projection mat, view mat, etc).
    //    // General uniforms should be set outside of the scope of RenderMeshObject
    //    // Seems in Stingray they are all written to the command stream but with a global/local tag
    //    // it's a pointer (resources) in the stream, not sure where the resources are managed
    //    //
    //    // Lin 1/20/2017
    //    // investigate how stingray do this
    //    //
    //    // local shader uniforms(custom unifomrs in Horde3D): std::vector<ShaderVar> local_vars and a pointer to buffer memory
    //    // struct ShaderVar { uint32 offset (offset for pointer); uint8 type; uint32 num_elem; };
    //    // buffer can be hold in MaterialResource and MaterialResource belongs to a Mesh node
    //    //
    //    // global shader uniforms(camera matrix): there is a resource manager to deal with that in Stingray
    //    // I will put the RenderCamera into RenderContext for current dev stage, since RenderContext is passed
    //    // into XXXRenderDevice.
    //    bool useDebug = true;
    //    if (useDebug)
    //    {
    //        RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;
    //        scs->shader_handle = 0xFFFFFFFF; // use it to indicate the default shader in device

    //        ShaderVariable model_mat_var;
    //        model_mat_var.klass = shader_data::MATRIX4X4;
    //        model_mat_var.elements = 1;
    //        model_mat_var.offset = 0;
    //        model_mat_var.element_stride = 0;
    //        model_mat_var.semantic_name = "worldMat";
    //        scs->variables.push_back(model_mat_var);

    //        char* data_ptr = new char[4 * 4 * 4]; // for a float 4*4 matrix
    //        memcpy(data_ptr, &_model_mat(0, 0), 4 * 4 * 4);
    //        scs->data = (void*)data_ptr;

    //        RenderContext::Command setShaderObject = { 0,  (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
    //        context->commands().push_back(setShaderObject);
    //    }
    //    else
    //    {
    //        RenderContext::ShaderCmdStream* scs = new RenderContext::ShaderCmdStream;
    //        scs->shader_handle = _shader_object->render_resource_handle;
    //        // set data
    //        // set variable
    //        RenderContext::Command setShaderObject = { 0, (void*)scs, RenderContext::CommandType::BIND_SHADER_OBJECT };
    //        context->commands().push_back(setShaderObject);
    //    }

    //    RenderContext::Command triggerDraw = { 0, nullptr, RenderContext::CommandType::RENDER };
    //    context->commands().push_back(triggerDraw);
    //}



}
