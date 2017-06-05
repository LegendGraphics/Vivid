#include "../3rdparty/glew/include/GL/glew.h"

#include "renderer/device/GLRenderDevice.h"
#include "renderer/device/RenderContext.h"
#include "renderer/resource/RenderResourceContext.h"
#include "renderer/runtime/RenderCamera.h"
#include "renderer/resource/VertexLayout.h"
#include "renderer/resource/ResourceStream.h"

#include "math/Vector4.h"
#include "io/Logger.h"

namespace te
{
    static const char *defaultShaderVS =
        "#version 430\n"
        "uniform mat4 viewProjMat;\n"
        "uniform mat4 worldMat;\n"
        "in vec3 vertPos;\n"
        "in vec3 normal;\n"
        "out vec3 g_normal;\n"
        "void main() {\n"
        "	gl_Position = viewProjMat * worldMat * vec4( vertPos, 1.0 );\n"
        "   g_normal = normal;\n"
        "}\n";

    static const char *defaultShaderFS =
        "#version 430\n"
        "uniform vec4 color;\n"
        "in vec3 g_normal;\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = clamp(max(dot(normalize(g_normal),normalize(vec3(0.3,0.5,1))),0.0), 0, 1) * color;\n"
        "}\n";

    GLRenderDevice::GLRenderDevice()
        : RenderDevice()
    {

    }

    GLRenderDevice::~GLRenderDevice()
    {

    }

    bool GLRenderDevice::open()
    {
        char* vendor = (char*)glGetString(GL_VENDOR);
        char* renderer = (char*)glGetString(GL_RENDERER);
        char* version = (char*)glGetString(GL_VERSION);

        bool bOK = true;
        //bOK = bOK && createDefaultShader(getDefaultVSCode(), getDefaultFSCode(), _default_shader);

        testVao();

        _pending_mask = 0;

        return bOK;
    }

    void GLRenderDevice::close()
    {

    }

    void GLRenderDevice::dispatch(RenderContext * context)
    {
        // do actual command
        // in stingray, this is done by XXXRenderContext, which is an internal
        // class within XXXRenderDevice and has nothing to do with RenderContext
        // XXXRenderDevice may hold an immediate_context. For deferred rendering
        // there might be other context, need investigation

        // For current dev stage, we simply let the device do the actual command
        for (RenderContext::Command& command : context->commands())
        {
            if (RenderContext::CommandType::UPDATE_INDEX_BUFFER == command.command_type)
            {
                RenderContext::IndexCmdStream* c_stream = static_cast<RenderContext::IndexCmdStream*>(command.head);
                //_newIndexBuf = c_stream->bufHandle;
                //_indexFormat = c_stream->idxFormat;
                delete c_stream;
            }
            else if (RenderContext::CommandType::UPDATE_VERTEX_BUFFER == command.command_type)
            {
                RenderContext::VertexCmdStream* c_stream = static_cast<RenderContext::VertexCmdStream*>(command.head);
                // each shader has an array of a structure InputLayouts { bool valid; int8 attribIndices[16]; }
                // it's related to how the vertex buffer is organized in OpenGL
                _new_vao = c_stream->vao_handle;
                //_new_vao = _testVao;
                _cur_base_index = c_stream->base_index;
                _cur_base_vertex = c_stream->base_vertex;
                _cur_num_indices = c_stream->num_indices;
                //_cur_num_indices = 3;
                _pending_mask |= PM_VERTLAYOUT;
                delete c_stream;
            }
            else if (RenderContext::CommandType::BIND_SHADER_OBJECT == command.command_type)
            {
                // set camera
                RenderCamera* curCamera = context->_camera;
                // set view port to
                _vp_x = curCamera->getViewPort()[0];
                _vp_y = curCamera->getViewPort()[1];
                _vp_width = curCamera->getViewPort()[2];
                _vp_height = curCamera->getViewPort()[3];
                _pending_mask |= PM_VIEWPORT;


                // set shader
                RenderContext::ShaderCmdStream* c_stream = static_cast<RenderContext::ShaderCmdStream*>(command.head);

                // set uniform value from camera, may be not proper
                for (auto& uniform : c_stream->uniforms.getUniforms())
                {
                }

                // TODO: need to be changed, set uniform value in engine part
                if (c_stream->shader_handle != 0xFFFFFFFF)
                {
                    // TODO
                    // use setShaderConst()
                    // header of all uniform data is in ShaderCmdStream::data
                    // ShaderCmdStream::variables give information for how to read
                    for (auto& uniform : c_stream->uniforms.getUniforms())
                    {
                        setShaderConst(uniform.second.loc, shader_data::Class(uniform.second.value.type), &uniform.second.value.data);
                    }
                    delete c_stream;
                }
                else
                {
                    //// debug mode, use default shader
                    //if (_cur_shader_handle != _default_shader.shader_handle)
                    //    bindShader(_default_shader.shader_handle);

                    //// set view params
                    //if (_default_shader.uni_view_mat >= 0)
                    //    setShaderConst(_default_shader.uni_view_mat, shader_data::MATRIX4X4, curCamera->getViewMat());
                    //if (_default_shader.uni_proj_mat >= 0)
                    //    setShaderConst(_default_shader.uni_proj_mat, shader_data::MATRIX4X4, curCamera->getProjectionMat());
                    //if (_default_shader.uni_view_proj_mat >= 0)
                    //    setShaderConst(_default_shader.uni_view_proj_mat, shader_data::MATRIX4X4, curCamera->getViewProjctionMat());

                    //char* data_ptr = static_cast<char*>(c_stream->data);
                    //for (auto i : c_stream->variables)
                    //{
                    //    setShaderConst(_default_shader.custom_uniform_handles[i.semantic_name], shader_data::Class(i.klass), data_ptr + i.offset);
                    //}
                    //delete[] data_ptr;

                    //// set default color
                    //float color[4] = { 0.75f, 0.5, 0.25f, 1 };
                    //setShaderConst(_default_shader.custom_uniform_handles["color"], shader_data::VECTOR4, &color);

                    //delete c_stream;
                }
            }
            else if (RenderContext::CommandType::SET_CAMERA == command.command_type)
            {
                RenderContext::CameraCmdStream* c_stream = static_cast<RenderContext::CameraCmdStream*>(command.head);
                _vp_x = c_stream->view_port.x;
                _vp_y = c_stream->view_port.y;
                _vp_width = c_stream->view_port.z;
                _vp_height = c_stream->view_port.w;
                _pending_mask |= PM_VIEWPORT;

                GLShader& cur_shader = _shaders.getRef(_cur_shader_handle);
                int proj_mat_loc = getShaderConstLoc(cur_shader.gl_program_obj, "projMat");
                int view_mat_loc = getShaderConstLoc(cur_shader.gl_program_obj, "viewMat");

                if (proj_mat_loc == -1) cLog << "Could not find uniform projMat in current shader";
                if (view_mat_loc == -1) cLog << "Could not find uniform viewMat in current shader";

                setShaderConst(proj_mat_loc, shader_data::MATRIX4X4, &c_stream->proj_mat);
                setShaderConst(view_mat_loc, shader_data::MATRIX4X4, &c_stream->view_mat);
            }
            else if (RenderContext::CommandType::SET_CAMERA == command.command_type)
            {
                RenderContext::SpaceCmdStream* c_stream = static_cast<RenderContext::SpaceCmdStream*>(command.head);
                GLShader& cur_shader = _shaders.getRef(_cur_shader_handle);
                int world_mat_loc = getShaderConstLoc(cur_shader.gl_program_obj, "worldMat");

                if (world_mat_loc == -1) cLog << "Could not find uniform worldMat in current shader";

                setShaderConst(world_mat_loc, shader_data::MATRIX4X4, &c_stream->world_mat);

            }
            else if (RenderContext::CommandType::RENDER == command.command_type)
            {
                draw();
            }
            else if (RenderContext::CommandType::CLEAR == command.command_type)
            {
                RenderContext::ClearCmdStream* c_stream = static_cast<RenderContext::ClearCmdStream*>(command.head);
                clear(c_stream->clear_color, c_stream->color_rgba, c_stream->clear_depth, c_stream->depth);
                delete c_stream;
            }
            else if (RenderContext::CommandType::SET_RENDER_TARGET == command.command_type)
            {

            }
        }

        context->commands().clear();
    }

    void GLRenderDevice::dispatch(RenderResourceContext * context)
    {
        for (RenderResourceContext::Message& msg : context->messages())
        {
            if (RenderResourceContext::MessageType::ALLOC_INDEX_BUFFER == msg.type)
            {
                // default type unsigned int
                vertex_layout::IndexStream* i_stream
                    = static_cast<vertex_layout::IndexStream*>(msg.head);
                GPUResourceHandle* res = i_stream->res;
                //ASSERT(RenderResource::INDEX_STREAM == res->type, "Render Resource Type doesn't match!");
                (*res) = createIndexBuffer(i_stream->size, i_stream->raw_data);
                
                delete i_stream;
            }
            else if (RenderResourceContext::MessageType::ALLOC_VERTEX_BUFFER == msg.type)
            {
                // default type float
                vertex_layout::VertexStream* v_stream
                    = static_cast<vertex_layout::VertexStream*>(msg.head);
                GPUResourceHandle* res = v_stream->res;
                //ASSERT(RenderResource::VERTEX_STREAM == res->type, "Render Resource Type doesn't match!");
                (*res) = createVertexBuffer(v_stream->size, v_stream->stride, v_stream->raw_data);

                delete v_stream;
            }
            else if (RenderResourceContext::MessageType::ALLOC_VERTEX_DECLARATION == msg.type)
            {
                vertex_layout::VertexDeclarationStream* vd_stream
                    = static_cast<vertex_layout::VertexDeclarationStream*>(msg.head);
                GPUResourceHandle* res = vd_stream->res;
                //ASSERT(RenderResource::VERTEX_DECLARATION == res->type, "Render Resource Type doesn't match!");

                const VertexLayout& vl = _vertex_declaration->getLayout(vd_stream->layout_type);
                // rearrange the vertex buffers here
                std::vector<GPUResourceHandle*> rearrangedVertexBuffers;
                for (const VertexLayoutAttrib& attr : vl)
                {
                    rearrangedVertexBuffers.push_back(vd_stream->vertex_buffers[attr.vb_slot]);
                }
                vd_stream->vertex_buffers.swap(rearrangedVertexBuffers);

                // compute stride for each slot          
                std::unordered_map<uint32, uint32> slotStrideMap;
                std::unordered_map<uint32, uint32>::iterator iter;
                for (const auto& i : vl)
                {
                    iter = slotStrideMap.find(i.vb_slot);
                    if (iter != slotStrideMap.end())
                        iter->second += i.size;
                    else
                        slotStrideMap[i.vb_slot] = i.size;
                }
                //ASSERT(vl.size() == vd_stream->vertex_buffers.size(),
                //    "Requested Num of Vertex Attribute Slots should have same Num of Vertex Buffers!");

                // prepare parameters for creating VAO
                std::vector<uint32> locations;
                std::vector<uint32> sizes;
                std::vector<uint32> offsets;
                std::vector<uint32> vertex_handles;
                for (uint32 i = 0; i < vl.size(); ++i)
                {
                    auto& attri = vl[i];
                    locations.push_back(i);
                    sizes.push_back(attri.size);
                    offsets.push_back(attri.offset);

                    uint32 buffer_handle = *(vd_stream->vertex_buffers[i]);
                    vertex_handles.push_back(buffer_handle);

                    uint32 stride_in_buffer = _buffers.getRef(buffer_handle).stride / 4; // unit of stride in buffer is in bytes
                    uint32 stride_in_slot = slotStrideMap[attri.vb_slot];
                    //ASSERT(stride_in_buffer == stride_in_slot, "Stride in Buffer should match Stride in Slot!");
                }
                uint32 index_handle = (*vd_stream->index_buffer);
                (*res) = createVertexArray(
                    locations.size(),
                    &locations[0],
                    &sizes[0],
                    &offsets[0],
                    &vertex_handles[0],
                    index_handle);

                delete vd_stream;
            }
            else if (RenderResourceContext::MessageType::ALLOC_SHADER == msg.type)
            {
                shader_data::ShaderStream* s_stream
                    = static_cast<shader_data::ShaderStream*>(msg.head);
                GPUResourceHandle* res = s_stream->res;
                (*res) = createShader(s_stream->vs.c_str(), s_stream->fs.c_str(), vertex_layout::PNTB);
                bindShader(*res);

                for (auto& uniform : s_stream->uniforms->getUniforms())
                {
                    uniform.second.loc = getShaderConstLoc(*res, uniform.first.c_str());
                }

                delete s_stream;
            }
            else if (RenderResourceContext::MessageType::ALLOC_TEXTURE == msg.type)
            {

                //GPUResourceHandle res = createTexture(int width, int height, int depth, image_data::Type type, image_data::Format format, bool has_mips)
            }
        }

        context->messages().clear();
    }

    void GLRenderDevice::clear(bool clear_color, float color_rgba[4], bool clear_depth, float depth)
    {
        uint32 gl_clear_mask = 0;
        if (clear_color)
        {
            gl_clear_mask |= GL_DEPTH_BUFFER_BIT;
            glClearColor(color_rgba[0], color_rgba[1], color_rgba[2], color_rgba[3]);
        }
        if (clear_depth)
        {
            gl_clear_mask |= GL_COLOR_BUFFER_BIT;
            glClearDepth(depth);
        }

        if (gl_clear_mask)
        {
            commitStates(PM_VIEWPORT);
            glClear(gl_clear_mask);
        }
    }

    uint32 GLRenderDevice::createVertexBuffer(uint32 size, uint32 stride, const void * data)
    {
        GLBuffer buf;
        buf.type = GL_ARRAY_BUFFER;
        buf.size = size;
        buf.stride = stride;
        glGenBuffers(1, &buf.gl_obj);
        glBindBuffer(buf.type, buf.gl_obj);
        glBufferData(buf.type, size, data, GL_DYNAMIC_DRAW);
        glBindBuffer(buf.type, 0);

        return _buffers.add(buf);
    }

    uint32 GLRenderDevice::createIndexBuffer(uint32 size, const void * data)
    {
        GLBuffer buf;

        buf.type = GL_ELEMENT_ARRAY_BUFFER;
        buf.size = size;
        buf.stride = 1 * 4; // if we use VAO, index buffer seems not important, it's stride in bytes
        glGenBuffers(1, &buf.gl_obj);
        glBindBuffer(buf.type, buf.gl_obj);
        glBufferData(buf.type, size, data, GL_DYNAMIC_DRAW);
        glBindBuffer(buf.type, 0);

        return _buffers.add(buf);
    }

    uint32 GLRenderDevice::createVertexArray(
        uint32 nLoc,
        const uint32 * locations,
        const uint32* sizes,
        const uint32 * offsets,
        const uint32 * vertex_handles,
        uint32 index_handle)
    {
        uint32 vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        for (uint32 i = 0; i < nLoc; ++i)
        {
            GLBuffer& v_buf = _buffers.getRef(vertex_handles[i]);
            glBindBuffer(v_buf.type, v_buf.gl_obj);
            glVertexAttribPointer(
                locations[i],
                sizes[i],
                GL_FLOAT,
                GL_FALSE,
                v_buf.stride,
                (void*)(offsets[i])); // offset in bytes which has been calculated in VertexLayout.cpp, no need to * 4
            //glEnableVertexArrayAttrib(vao, locations[i]); // found a potential problem here, this function is only available since OpenGL 4.5
            glEnableVertexAttribArray(locations[i]);
        }

        GLBuffer& i_buf = _buffers.getRef(index_handle);
        glBindBuffer(i_buf.type, i_buf.gl_obj); // bind index buffer to VAO

        glBindVertexArray(0);
        return _vaos.add(vao);
    }

    void GLRenderDevice::destroyBuffer(uint32 buf_obj)
    {
        if (0 == buf_obj) return;

        GLBuffer& buf = _buffers.getRef(buf_obj);
        glDeleteBuffers(1, &buf.gl_obj);

        _buffers.remove(buf_obj);
    }

    void GLRenderDevice::updateBufferData(uint32 buf_obj, uint32 offset, uint32 size, void * data)
    {
        const GLBuffer& buf = _buffers.getRef(buf_obj);
       // ASSERT(offset + size <= buf.size, "offset + size should be no larger than buf.size!");

        glBindBuffer(buf.type, buf.gl_obj);
        
        if (0 == offset && size == buf.size)
        {
            glBufferData(buf.type, size, data, GL_DYNAMIC_DRAW);
            return;
        }

        glBufferSubData(buf.type, offset, size, data);
    }

    const char* GLRenderDevice::getDefaultVSCode()
    {
        return defaultShaderVS;
    }

    const char* GLRenderDevice::getDefaultFSCode()
    {
        return defaultShaderFS;
    }

    te::uint32 GLRenderDevice::createShader(const char* vertex_shader_src, const char* fragment_shader_src, vertex_layout::Type vl_type)
    {
        uint32 program_obj = createShaderProgram(vertex_shader_src, fragment_shader_src);
        if (0 == program_obj) return 0;
        if (!configShaderVertexLayout(program_obj, vl_type)) return 0;
        if (!linkShaderProgram(program_obj)) return 0;

        uint32 shader_handle = _shaders.add(GLShader());
        GLShader& shader = _shaders.getRef(shader_handle);
        shader.gl_program_obj = program_obj;

        return shader_handle;
    }

    uint32 GLRenderDevice::createShaderProgram(const char * vertex_shader_src, const char * fragment_shader_src)
    {
        int info_log_length = 0;
        int chars_written = 0;
        char *info_log = 0x0;
        int status;

        // vertex shader
        uint32 vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex_shader_src, 0x0);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            // Get info
            glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &info_log_length);
            if (info_log_length > 1)
            {
                info_log = new char[info_log_length];
                glGetShaderInfoLog(vs, info_log_length, &chars_written, info_log);
                _shader_log = _shader_log + "[Vertex Shader]\n" + info_log;
                delete[] info_log; info_log = 0x0;
            }

            glDeleteShader(vs);
            return 0;
        }

        // Fragment shader
        uint32 fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment_shader_src, 0x0);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &info_log_length);
            if (info_log_length > 1)
            {
                info_log = new char[info_log_length];
                glGetShaderInfoLog(fs, info_log_length, &chars_written, info_log);
                _shader_log = _shader_log + "[Fragment Shader]\n" + info_log;
                delete[] info_log; info_log = 0x0;
            }

            glDeleteShader(vs);
            glDeleteShader(fs);
            return 0;
        }

        // Shader program
        uint32 program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    bool GLRenderDevice::configShaderVertexLayout(uint32 program_obj, vertex_layout::Type vl_type)
    {
        const VertexLayout& vl = _vertex_declaration->getLayout(vl_type);
        for (uint32 i = 0; i < vl.size(); ++i)
        {
            glBindAttribLocation(program_obj, i, vl[i].semantic_name.c_str());
        }
        return true;
    }

    bool GLRenderDevice::linkShaderProgram(uint32 program_obj)
    {
        int info_log_length = 0;
        int chars_written = 0;
        char *info_log = 0x0;
        int status;

        _shader_log = "";

        glLinkProgram(program_obj);
        glGetProgramiv(program_obj, GL_INFO_LOG_LENGTH, &info_log_length);
        if (info_log_length > 1)
        {
            info_log = new char[info_log_length];
            glGetProgramInfoLog(program_obj, info_log_length, &chars_written, info_log);
            _shader_log = _shader_log + "[Linking]\n" + info_log;
            delete[] info_log; info_log = 0x0;
        }

        glGetProgramiv(program_obj, GL_LINK_STATUS, &status);
        if (!status) return false;

        return true;
    }

    int GLRenderDevice::getShaderConstLoc(uint32 shader_handle, const char* name)
    {
        GLShader& shader = _shaders.getRef(shader_handle);
        return glGetUniformLocation(shader.gl_program_obj, name);
    }

    void GLRenderDevice::setShaderConst(int loc, shader_data::Class type, void * values, uint32 count)
    {
        switch (type)
        {
        case shader_data::SCALAR:
            glUniform1fv(loc, count, (float*)values);
            break;
        case shader_data::VECTOR2:
            glUniform2fv(loc, count, (float*)values);
            break;
        case shader_data::VECTOR3:
            glUniform3fv(loc, count, (float*)values);
            break;
        case shader_data::VECTOR4:
            glUniform4fv(loc, count, (float*)values);
            break;
        case shader_data::MATRIX4X4:
            glUniformMatrix4fv(loc, count, true, (float*)values);
            break;
        }
    }

    void GLRenderDevice::bindShader(uint32 shader_handle)
    {
        if (0 != shader_handle)
        {
            GLShader& shader = _shaders.getRef(shader_handle);
            glUseProgram(shader.gl_program_obj);
        }
        else
        {
            glUseProgram(0);
        }

        _cur_shader_handle = shader_handle;
    }

    uint32 GLRenderDevice::createRenderBuffer(uint32 width, uint32 height, image_data::Format format, bool depth, uint32 num_col_bufs)
    {
        GLRenderTarget render_target;
        glGenFramebuffers(1, &render_target.gl_fbo);

        if (num_col_bufs > 0)
        {
            for (uint32 i = 0; i < num_col_bufs; ++i)
            {
                glBindFramebuffer(GL_FRAMEBUFFER, render_target.gl_fbo);
                // create color texture
                uint32 tex_obj = createTexture(width, height, 1, image_data::IMAGE2D, image_data::RGBA32F, false);
               // ASSERT(tex_obj != 0, "Not a Valid Texture Object!");
                updateTextureData(tex_obj, 0, nullptr);
                // attach the texture to fbo
                GLTexture& tex = _textures.getRef(tex_obj);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex.gl_obj, 0);
            }
        }

        uint32 buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        glBindFramebuffer(GL_FRAMEBUFFER, render_target.gl_fbo);
        glDrawBuffers(num_col_bufs, buffers);

        if (depth)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, render_target.gl_fbo);
            // create a depth texture
            uint32 tex_obj = createTexture(width, height, 1, image_data::IMAGE2D, image_data::DEPTH, false);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
            updateTextureData(tex_obj, 0, nullptr);
            GLTexture& tex = _textures.getRef(tex_obj);
            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex.gl_obj, 0);
        }

        // check if everything is OK
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, render_target.gl_fbo);
        GLenum e = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
       // ASSERT(e != GL_FRAMEBUFFER_COMPLETE, "There is a problem with the FBO");
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        return _render_targets.add(render_target);
    }

    uint32 GLRenderDevice::createTexture(int width, int height, int depth, image_data::Type type, image_data::Format format, bool has_mips)
    {
        GLTexture tex;
        tex.format = format;
        tex.width = width;
        tex.height = height;
        tex.depth = depth;
        tex.has_mips = has_mips;

        switch (type)
        {
        case image_data::IMAGE2D:
            tex.gl_type = GL_TEXTURE_2D;
            break;
        case image_data::IMAGE3D:
            tex.gl_type = GL_TEXTURE_3D;
            break;
        case image_data::IMAGECUBE:
            tex.gl_type = GL_TEXTURE_CUBE_MAP;
            break;
        }

        glGenTextures(1, &tex.gl_obj);
        glActiveTexture(GL_TEXTURE0 + 15); // assume the 16th texture unit isn't usually used
        glBindTexture(tex.gl_type, tex.gl_obj);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        return _textures.add(tex);
    }

    void GLRenderDevice::updateTextureData(uint32 tex_obj, int mip_level, const void* pixels)
    {
        const GLTexture tex = _textures.getRef(tex_obj);

        glBindTexture(tex.gl_type, tex.gl_obj);

        int input_format = GL_BGRA, input_type = GL_UNSIGNED_BYTE;
        switch (tex.format)
        {
        case image_data::RGBA16F:
            input_format = GL_RGBA;
            input_type = GL_FLOAT;
            break;
        case image_data::RGBA32F:
            input_format = GL_RGBA;
            input_type = GL_FLOAT;
            break;
        case image_data::DEPTH:
            input_format = GL_DEPTH_COMPONENT;
            input_type = GL_FLOAT;
        };
        glTexImage2D(tex.gl_type, mip_level, input_format, tex.width, tex.height, 0, input_format, input_type, pixels);
        glBindTexture(tex.gl_type, 0);
    }

    void GLRenderDevice::commitGeneralUniforms()
    {

    }

    void GLRenderDevice::draw()
    {
        if (commitStates())
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            // base index is the start index of sub-component (3*numFace)
            // base vertex is the start vertex of sub-component (3*numVert)
            glDrawElementsBaseVertex(GL_TRIANGLES,
                _cur_num_indices,
                GL_UNSIGNED_INT,
                (void*)(sizeof(unsigned int)*_cur_base_index),
                _cur_base_vertex);
            //glDrawArrays(GL_TRIANGLES, 0, _cur_num_indices);
        }
    }

    bool GLRenderDevice::commitStates(uint32 filter)
    {
      if (_pending_mask & filter)
      {
        uint32 mask = _pending_mask & filter;

        if (mask & PM_VIEWPORT)
        {
          glViewport(_vp_x, _vp_y, _vp_width, _vp_height);
          _pending_mask &= ~PM_VIEWPORT;
        }

        if (mask & PM_VERTLAYOUT)
        {
          _cur_vao = _new_vao;
          _prev_shader_handle = _cur_shader_handle;

          glBindVertexArray(_vaos.getRef(_cur_vao));
        }
      }
      return true;
    }

    void GLRenderDevice::testVao()
    {
        const float tris[6][3] = {
            { 0.0,  0.0,  0.0 },
            { 0.0,  0.0,  0.0 },
            { 1.0,  0.0,  0.0 },
            { 0.0,  0.5,  0.0 },
            { 0.0,  1.0,  0.0 },
            {-1.0,  0.0,  0.0 }
        };

        _testVbo = createVertexBuffer(18 * 4, 6, tris);

        const uint32 idxs[1][3] = {
            { 0, 1, 2}
        };

        _testIbo = createIndexBuffer(3 * 4, idxs);

        uint32 nLoc = 1;
        uint32 locations[1] = { 0 };
        uint32 sizes[1] = { 3 };
        uint32 offsets[1] = { 3 };
        uint32 vertex_handles[1] = { _testVbo };
        uint32 index_handle = _testIbo;

        _testVao = createVertexArray(nLoc, locations, sizes, offsets, vertex_handles, index_handle);
    }

    /*bool GLRenderDevice::createDefaultShader(const char* vertex_shader, const char* fragment_shader, ShaderObject& so)
    {
        uint32 shader_handle = createShader(vertex_shader, fragment_shader, vertex_layout::PNTB);
        if (0 == shader_handle) return false;

        so.shader_handle = shader_handle;
        bindShader(shader_handle);

        so.custom_uniform_handles["color"] = getShaderConstLoc(shader_handle, "color");
        so.custom_uniform_handles["worldMat"] = getShaderConstLoc(shader_handle, "worldMat");

        so.uni_view_mat = getShaderConstLoc(shader_handle, "viewMat");
        so.uni_proj_mat = getShaderConstLoc(shader_handle, "projMat");
        so.uni_view_proj_mat = getShaderConstLoc(shader_handle, "viewProjMat");
        so.uni_view_proj_mat_inv = getShaderConstLoc(shader_handle, "viewProjMatInv");

        return true;
    }*/
}