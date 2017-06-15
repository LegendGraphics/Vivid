#include "io/ResourceLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "io/Logger.h"
#include "io/FileUtils.h"
#include "common/Mesh.h"
#include "common/Pipeline.h"
#include "common/Node.h"
#include "common/SpaceState.h"
#include "common/MeshRender.h"
#include "common/Texture.h"
#include "common/Material.h"
#include "common/Shader.h"
#include "common/Uploader.h"

namespace te
{
    String ResourceLoader::_data_path = "";
    void ResourceLoader::setDataPath(const String& res)
    {
        ResourceLoader::_data_path = res;
    }

    bool ResourceLoader::load(Mesh* mesh, const String& res)
    {
        char *data_ptr = nullptr;
        int size = 0;

        FileUtils::streamFromBinaryFile(_data_path + res, data_ptr, size);

        // Check header and version
        char id[3];
        memcpy(&id, data_ptr, 3); data_ptr += 3;
        if (id[0] != 'T' || id[1] != 'E' || id[2] != 'M')
            return false; //("Invalid mesh resource");

        int version;
        memcpy(&version, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        if (version != 1)
            return false; //("Unsupported version of mesh resource");

        int vertex_type;
        memcpy(&vertex_type, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        mesh->_layout_type = vertex_layout::Type(vertex_type);

        // Load mesh data
        // vertex stream
        int attribute_num;
        memcpy(&attribute_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

        int vertex_num;
        memcpy(&vertex_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

        mesh->_vertices.convert(vertex_layout::Type(vertex_type));
        mesh->_vertices.initialize(vertex_num);


        for (int i = 0; i < attribute_num; ++i)
        {
            short sh;
            int stream_id, elem_size;
            memcpy(&stream_id, data_ptr, sizeof(int)); data_ptr += sizeof(int);
            memcpy(&elem_size, data_ptr, sizeof(int)); data_ptr += sizeof(int);
            String errormsg;

            if (stream_id == vertex_layout::VertexAttribute::POSITION)
            {
                if (elem_size != 12)
                {
                    errormsg = "Invalid position base stream";
                    break;
                }
                for (int j = 0; j < vertex_num; ++j)
                {
                    memcpy(&mesh->_vertices.position(j).x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                    memcpy(&mesh->_vertices.position(j).y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                    memcpy(&mesh->_vertices.position(j).z, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                }
            }
            else if (stream_id == vertex_layout::VertexAttribute::NORMAL)
            {
                if (elem_size != 6)
                {
                    errormsg = "Invalid normal base stream";
                    break;
                }
                for (int j = 0; j < vertex_num; ++j)
                {
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.normal(j).x = sh / 32767.0f;
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.normal(j).y = sh / 32767.0f;
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.normal(j).z = sh / 32767.0f;
                }
            }
            else if (stream_id == vertex_layout::VertexAttribute::TANGENT)
            {
                if (elem_size != 6)
                {
                    errormsg = "Invalid tangent base stream";
                    break;
                }
                for (int j = 0; j < vertex_num; ++j)
                {
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.tangent(j).x = sh / 32767.0f;
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.tangent(j).y = sh / 32767.0f;
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.tangent(j).z = sh / 32767.0f;
                }
            }
            else if (stream_id == vertex_layout::VertexAttribute::BITANGENT)
            {
                if (elem_size != 6)
                {
                    errormsg = "Invalid bitangent base stream";
                    break;
                }
                for (int j = 0; j < vertex_num; ++j)
                {
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.bitangent(j).x = sh / 32767.0f;
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.bitangent(j).y = sh / 32767.0f;
                    memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.bitangent(j).z = sh / 32767.0f;
                }
            }
            else if (stream_id == vertex_layout::VertexAttribute::TEXTURE1)
            {
                if (elem_size != 8)
                {
                    errormsg = "Invalid texture 1 base stream";
                    break;
                }
                for (int j = 0; j < vertex_num; ++j)
                {
                    memcpy(&mesh->_vertices.tex(j, 0).x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                    memcpy(&mesh->_vertices.tex(j, 0).y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                }
            }
            else if (stream_id == vertex_layout::VertexAttribute::TEXTURE2)
            {
                if (elem_size != 8)
                {
                    errormsg = "Invalid texture 2 base stream";
                    break;
                }
                for (int j = 0; j < vertex_num; ++j)
                {
                    memcpy(&mesh->_vertices.tex(j, 1).x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                    memcpy(&mesh->_vertices.tex(j, 1).y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                }
            }
        }

        //for (int i = 0; i < attribute_num; ++i)
        //{
        //    short sh;
        //    int stream_id, elem_size;
        //    memcpy(&stream_id, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        //    memcpy(&elem_size, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        //    String errormsg;

        //    switch (stream_id)
        //    {
        //    case 0:		// Position
        //        if (elem_size != 12)
        //        {
        //            errormsg = "Invalid position base stream";
        //            break;
        //        }
        //        for (int j = 0; j < vertex_num; ++j)
        //        {
        //            memcpy(&mesh->_vertices.position(j).x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
        //            memcpy(&mesh->_vertices.position(j).y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
        //            memcpy(&mesh->_vertices.position(j).z, data_ptr, sizeof(float)); data_ptr += sizeof(float);
        //        }
        //        break;
        //    case 1:		// Normal
        //        if (elem_size != 6)
        //        {
        //            errormsg = "Invalid normal base stream";
        //            break;
        //        }
        //        for (int j = 0; j < vertex_num; ++j)
        //        {
        //            memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.normal(j).x = sh / 32767.0f;
        //            memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.normal(j).y = sh / 32767.0f;
        //            memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.normal(j).z = sh / 32767.0f;
        //        }
        //        break;
        //        //case 2:		// Tangent
        //        //    if (elem_size != 6)
        //        //    {
        //        //        errormsg = "Invalid tangent base stream";
        //        //        break;
        //        //    }
        //        //    for (int j = 0; j < vertex_num; ++j)
        //        //    {
        //        //        memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.tangent(j).x = sh / 32767.0f;
        //        //        memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.tangent(j).y = sh / 32767.0f;
        //        //        memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.tangent(j).z = sh / 32767.0f;
        //        //    }
        //        //    break;
        //        //case 3:		// Bitangent
        //        //    if (elem_size != 6)
        //        //    {
        //        //        errormsg = "Invalid bitangent base stream";
        //        //        break;
        //        //    }
        //        //    for (int j = 0; j < vertex_num; ++j)
        //        //    {
        //        //        memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.bitangent(j).x = sh / 32767.0f;
        //        //        memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.bitangent(j).y = sh / 32767.0f;
        //        //        memcpy(&sh, data_ptr, sizeof(short)); data_ptr += sizeof(short); mesh->_vertices.bitangent(j).z = sh / 32767.0f;
        //        //    }
        //        //    break;
        //    case 2:		// Texture1
        //        if (elem_size != 8)
        //        {
        //            errormsg = "Invalid texture 1 base stream";
        //            break;
        //        }
        //        for (int j = 0; j < vertex_num; ++j)
        //        {
        //            //float a, b;
        //            //memcpy(&a, data_ptr, sizeof(float)); data_ptr += sizeof(float);
        //            //memcpy(&b, data_ptr, sizeof(float)); data_ptr += sizeof(float);

        //            memcpy(&mesh->_vertices.tex(j, 0).x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
        //            memcpy(&mesh->_vertices.tex(j, 0).y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
        //        }
        //        break;
        //        //case 5:		// Texture2
        //        //    if (elem_size != 8)
        //        //    {
        //        //        errormsg = "Invalid texture 2 base stream";
        //        //        break;
        //        //    }
        //        //    for (int j = 0; j < vertex_num; ++j)
        //        //    {
        //        //        memcpy(&sh, data_ptr, sizeof(float)); data_ptr += sizeof(float); mesh->_vertices.tex(j, 1).x = sh;
        //        //        memcpy(&sh, data_ptr, sizeof(float)); data_ptr += sizeof(float); mesh->_vertices.tex(j, 1).y = sh;
        //        //    }
        //        //    break;

        //    default:
        //        data_ptr += elem_size * vertex_num;
        //        continue;
        //    }
        //    cLog << errormsg;
        //}

        // triangle stream
        int indice_num;
        memcpy(&indice_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

        mesh->_triangles.resize(indice_num);
        for (int i = 0; i < indice_num; ++i)
        {
            memcpy(&mesh->_triangles[i], data_ptr, sizeof(int)); data_ptr += sizeof(int);
        }

        return true;
    }

    bool ResourceLoader::load(MetaNode* meta_node, const String& res)
    {
        char *data = nullptr;
        int size = 0;

        FileUtils::streamFromBinaryFile(_data_path + res, data, size);

        XMLDoc doc;
        doc.parseBuffer(data, size);
        if (doc.hasError())
        {
            cLog << "XML parsing error";
            return false;
        }

        XMLNode root_node = doc.getRootNode();
        if (strcmp(root_node.getName(), "Node") != 0)
        {
            cLog << "Not a node resource file";
            return false;
        }

        XMLNode com_node = root_node.getFirstChild("Components");
        if (strcmp(com_node.getName(), "Components") != 0) return false;

        XMLNode node1 = com_node.getFirstChild();
        while (!node1.isEmpty())
        {
            if (strcmp(node1.getName(), "SpaceState") == 0)
            {
                XMLNode position_node = node1.getFirstChild("Position");
                float px = (float)atof(position_node.getAttribute("x", "0"));
                float py = (float)atof(position_node.getAttribute("y", "0"));
                float pz = (float)atof(position_node.getAttribute("z", "0"));

                XMLNode scale_node = node1.getFirstChild("Scale");
                float sx = (float)atof(scale_node.getAttribute("x", "0"));
                float sy = (float)atof(scale_node.getAttribute("y", "0"));
                float sz = (float)atof(scale_node.getAttribute("z", "0"));

                XMLNode rotation_node = node1.getFirstChild("Rotation");
                float rx = (float)atof(rotation_node.getAttribute("x", "0"));
                float ry = (float)atof(rotation_node.getAttribute("y", "0"));
                float rz = (float)atof(rotation_node.getAttribute("z", "0"));

                SpaceState* space_status = new SpaceState(Vector3(px, py, pz), Vector3(sx, sy, sz), Vector3(rx, ry, rz));
                meta_node->components.push_back(space_status);
            }
            else if (strcmp(node1.getName(), "MeshRender") == 0)
            {
                XMLNode geo_node = node1.getFirstChild("Geometry");
                String geo_name = geo_node.getAttribute("name");

                XMLNode mat_node = node1.getFirstChild("Material");
                String mat_name = mat_node.getAttribute("name");

                MeshRender* mesh_render = new MeshRender(ASSETS_PATH + geo_name, ASSETS_PATH + mat_name);
                meta_node->components.push_back(mesh_render);
            }
            else if (strcmp(node1.getName(), "UploadToRender") == 0)
            {
                UploadToRender* uploader = new UploadToRender();
                meta_node->components.push_back(uploader);
            }
            else if (strcmp(node1.getName(), "CameraState") == 0)
            {
                XMLNode camera_node = node1.getFirstChild("Camera");
                String camera_name = camera_node.getAttribute("name");

                CameraState* camera_state = new CameraState();
                load(camera_state, camera_name);
                meta_node->components.push_back(camera_state);
            }

            node1 = node1.getNextSibling();
        }


        return true;
    }

    bool ResourceLoader::load(Pipeline* pipeline, const String& res)
    {
        char *data = nullptr;
        int size = 0;

        FileUtils::streamFromBinaryFile(_data_path + res, data, size);

        XMLDoc doc;
        doc.parseBuffer(data, size);
        if (doc.hasError())
        {
            cLog << "XML parsing error";
            return false;
        }

        XMLNode rootNode = doc.getRootNode();
        if (strcmp(rootNode.getName(), "Pipeline") != 0)
        {
            cLog << "Not a pipeline resource file";
            return false;
        }

        // Parse setup
        XMLNode node1 = rootNode.getFirstChild("Setup");
        if (!node1.isEmpty())
        {
            XMLNode node2 = node1.getFirstChild("RenderTarget");
            while (!node2.isEmpty())
            {
                // TODO: about render target
                node2 = node2.getNextSibling("RenderTarget");
            }
        }

        // Parse commands
        node1 = rootNode.getFirstChild("CommandQueue");
        if (!node1.isEmpty())
        {
            pipeline->getStages().reserve(node1.countChildNodes("Stage"));

            XMLNode node2 = node1.getFirstChild("Stage");
            while (!node2.isEmpty())
            {
                pipeline->getStages().push_back(PipelineStage());
                String errorMsg = ResourceLoader::parseStage(node2, &pipeline->getStages().back());
                if (errorMsg != "")
                {
                    cLog << StringUtils::format("Error in stage %s: %s", pipeline->getStages().back().id, errorMsg);
                    return false;
                }

                node2 = node2.getNextSibling("Stage");
            }
        }

        return true;
    }


    const String ResourceLoader::parseStage(XMLNode& node, PipelineStage* cur_stage)
    {
        PipelineStage& stage = *cur_stage;
        stage.id = node.getAttribute("id", "");

        if (strcmp(node.getAttribute("enabled", "true"), "false") == 0 ||
            strcmp(node.getAttribute("enabled", "1"), "0") == 0)
            stage.enabled = false;
        else
            stage.enabled = true;

        stage.commands.reserve(node.countChildNodes());

        // Parse commands
        XMLNode node1 = node.getFirstChild();
        while (!node1.isEmpty())
        {
            if (strcmp(node1.getName(), "BindBuffer") == 0)
            {
                if (!node1.getAttribute("sampler") || !node1.getAttribute("sourceRT") || !node1.getAttribute("bufIndex"))
                    return "Missing BindBuffer attribute";

                PipelineCommand command(PipelineCommandType::BindBuffer);
                command.paras.push_back(String(node1.getAttribute("sourceRT")));
                command.paras.push_back(String(node1.getAttribute("sampler")));
                command.paras.push_back(String(node1.getAttribute("bufIndex")));
                stage.commands.push_back(command);
            }
            else if (strcmp(node1.getName(), "UnbindBuffers") == 0)
            {
                stage.commands.push_back(PipelineCommand(PipelineCommandType::UnbindBuffers));
            }
            else if (strcmp(node1.getName(), "ClearTarget") == 0)
            {
                PipelineCommand command(PipelineCommandType::ClearTarget);
                command.paras.resize(9);
                command.paras[0] = false;
                command.paras[1] = false;
                command.paras[2] = false;
                command.paras[3] = false;
                command.paras[4] = false;
                command.paras[5] = String(node1.getAttribute("col_R", "0"));
                command.paras[6] = String(node1.getAttribute("col_G", "0"));
                command.paras[7] = String(node1.getAttribute("col_B", "0"));
                command.paras[8] = String(node1.getAttribute("col_A", "0"));

                if (strcmp(node1.getAttribute("depthBuf", "false"), "true") == 0 ||
                    strcmp(node1.getAttribute("depthBuf", "0"), "1") == 0)
                {
                    command.paras[0] = true;
                }
                if (strcmp(node1.getAttribute("colBuf0", "false"), "true") == 0 ||
                    strcmp(node1.getAttribute("colBuf0", "0"), "1") == 0)
                {
                    command.paras[1] = true;
                }
                if (strcmp(node1.getAttribute("colBuf1", "false"), "true") == 0 ||
                    strcmp(node1.getAttribute("colBuf1", "0"), "1") == 0)
                {
                    command.paras[2] = true;
                }
                if (strcmp(node1.getAttribute("colBuf2", "false"), "true") == 0 ||
                    strcmp(node1.getAttribute("colBuf2", "0"), "1") == 0)
                {
                    command.paras[3] = true;
                }
                if (strcmp(node1.getAttribute("colBuf3", "false"), "true") == 0 ||
                    strcmp(node1.getAttribute("colBuf3", "0"), "1") == 0)
                {
                    command.paras[4] = true;
                }

                stage.commands.push_back(command);
            }
            else if (strcmp(node1.getName(), "DrawGeometry") == 0)
            {
                if (!node1.getAttribute("context")) return "Missing DrawGeometry attribute 'context'";

                PipelineCommand command(PipelineCommandType::DrawGeometry);
                command.paras.push_back(String(node1.getAttribute("context")));
                command.paras.push_back(String(node1.getAttribute("class")));
                command.paras.push_back(String(node1.getAttribute("order")));
                stage.commands.push_back(command);
            }
            else if (strcmp(node1.getName(), "DrawOverlays") == 0)
            {
                if (!node1.getAttribute("context")) return "Missing DrawOverlays attribute 'context'";

                PipelineCommand command(PipelineCommandType::DrawOverlays);
                command.paras.push_back(String(node1.getAttribute("context")));
                stage.commands.push_back(command);
            }
            else if (strcmp(node1.getName(), "DrawQuad") == 0)
            {
                if (!node1.getAttribute("material")) return "Missing DrawQuad attribute 'material'";
                if (!node1.getAttribute("context")) return "Missing DrawQuad attribute 'context'";

                PipelineCommand command(PipelineCommandType::DrawQuad);
                command.paras.push_back(String(node1.getAttribute("material")));
                command.paras.push_back(String(node1.getAttribute("context")));
            }
            else if (strcmp(node1.getName(), "DoForwardLightLoop") == 0)
            {
                PipelineCommand command(PipelineCommandType::DoForwardLightLoop);
                command.paras.push_back(String(node1.getAttribute("class")));
                command.paras.push_back(String(node1.getAttribute("context")));
                command.paras.push_back(String(node1.getAttribute("order")));
                command.paras.push_back(String(node1.getAttribute("noShadows")));
                stage.commands.push_back(command);
            }
            else if (strcmp(node1.getName(), "DoDeferredLightLoop") == 0)
            {
                PipelineCommand command(PipelineCommandType::DoDeferredLightLoop);
                command.paras.push_back(String(node1.getAttribute("context")));
                stage.commands.push_back(command);
            }
            else if (strcmp(node1.getName(), "SetUniform") == 0)
            {
                if (!node1.getAttribute("material")) return "Missing SetUniform attribute 'material'";
                if (!node1.getAttribute("uniform")) return "Missing SetUniform attribute 'uniform'";

                PipelineCommand command(PipelineCommandType::SetUniform);
                command.paras.push_back(String(node1.getAttribute("material")));
                command.paras.push_back(String(node1.getAttribute("uniform")));
                command.paras.push_back(String(node1.getAttribute("a", "0")));
                command.paras.push_back(String(node1.getAttribute("b", "0")));
                command.paras.push_back(String(node1.getAttribute("c", "0")));
                command.paras.push_back(String(node1.getAttribute("d", "0")));
                stage.commands.push_back(command);
            }

            node1 = node1.getNextSibling();
        }

        return "";
    }

    // using stb_image loader
    bool ResourceLoader::load(Texture* texture, const String& res)
    {
        int x, y, n;

        stbi_set_flip_vertically_on_load(1);
        unsigned char *data = stbi_load((_data_path + res).c_str(), &x, &y, &n, 0);

        if (data == nullptr) return false;

        texture->setData(data);
        texture->setWidth(x);
        texture->setHeight(y);
        texture->setDepth(n);

        return true;
    }


    bool ResourceLoader::load(Material* material, const String& res)
    {
        char *data = nullptr;
        int size = 0;

        FileUtils::streamFromBinaryFile(_data_path + res, data, size);

        XMLDoc doc;
        doc.parseBuffer(data, size);
        if (doc.hasError())
        {
            cLog << "XML parsing error";
            return false;
        }

        XMLNode rootNode = doc.getRootNode();
        if (strcmp(rootNode.getName(), "Material") != 0)
        {
            cLog << "Not a material resource file";
            return false;
        }

        // Shader
        XMLNode node1 = rootNode.getFirstChild("Shader");
        if (!node1.isEmpty())
        {
            if (node1.getAttribute("source") == 0x0)
            {
                cLog << "Missing Shader attribute 'source'";
                return false;
            }
            String shader_file = ASSETS_PATH + node1.getAttribute("source");
            material->_shader = ResourceMapper::getInstance()->get<ShaderManager>()->create(shader_file);
        }

        // Texture samplers
        node1 = rootNode.getFirstChild("Sampler");
        while (!node1.isEmpty())
        {
            if (node1.getAttribute("name") == 0x0)
            {
                cLog << "Missing Sampler attribute 'name'";
                return false;
            }
            if (node1.getAttribute("map") == 0x0)
            {
                cLog << "Missing Sampler attribute 'map'";
                return false;
            }

            String name = node1.getAttribute("name");
            String img = ASSETS_PATH + node1.getAttribute("map");
            ResourceHandle texture = ResourceMapper::getInstance()->get<TextureManager>()->create(img);
            material->setTexture(name, texture);

            node1 = node1.getNextSibling("Sampler");
        }

        // Uniform values
        node1 = rootNode.getFirstChild("Uniform");
        while (!node1.isEmpty())
        {
            if (node1.getAttribute("name") == 0x0)
            {
                cLog << "Missing Uniform attribute 'name'";
                return false;
            }
            String uniform_name = node1.getAttribute("name");
            Var a = String(node1.getAttribute("a", "0"));
            Var b = String(node1.getAttribute("b", "0"));
            Var c = String(node1.getAttribute("c", "0"));
            Var d = String(node1.getAttribute("d", "0"));

            material->setUniform(uniform_name, a.toFloat(), b.toFloat(),
                c.toFloat(), d.toFloat());

            node1 = node1.getNextSibling("Uniform");
        }

        return true;
    }


    bool ResourceLoader::load(Shader* shader, const String& res)
    {
        char *data = nullptr;
        int size = 0;
        FileUtils::streamFromBinaryFile(_data_path + res, data, size);
        if (data == nullptr) return false;

        XMLDoc doc;
        doc.parseBuffer(data, size);
        if (doc.hasError())
        {
            cLog << "XML parsing error";
            return false;
        }

        XMLNode rootNode = doc.getRootNode();
        if (strcmp(rootNode.getName(), "Shader") != 0)
        {
            cLog << "Not a shader resource file";
            return false;
        }

        // Parse uniforms
        XMLNode node1 = rootNode.getFirstChild("Uniforms");
        if (!node1.isEmpty())
        {
            XMLNode node2 = node1.getFirstChild("Uniform");
            while (!node2.isEmpty())
            {
                // TODO: add shader uniform
                String name = node2.getAttribute("name");
                String type = node2.getAttribute("type");

                // set uniform
                shader->uniforms.addUniform(name, Shader::uni_type_map[type]);
                node2 = node2.getNextSibling("Uniform");
            }
        }

        // Parse samplers
        node1 = rootNode.getFirstChild("Samplers");
        if (!node1.isEmpty())
        {
            int tex_unit = 0;   // indicate texture unit for current sampler
            XMLNode node2 = node1.getFirstChild("Sampler");
            while (!node2.isEmpty())
            {
                // TODO: add sampler uniform
                String name = node2.getAttribute("name");

                // set sampler uniform
                shader->samplers.addSampler(name, tex_unit++);
                node2 = node2.getNextSibling("Sampler");
            }
        }

        // Parse glsl, currently using vertex and fragment glsl file
        node1 = rootNode.getFirstChild("GLSL");
        if (!node1.isEmpty())
        {
            XMLNode vs_node = node1.getFirstChild("Vertex");
            String vertex_file = ASSETS_PATH + vs_node.getAttribute("name");
            shader->_vs_context = parseGLSL(vertex_file);

            XMLNode fs_node = node1.getFirstChild("Fragment");
            String fragment_file = ASSETS_PATH + fs_node.getAttribute("name");
            shader->_fs_context = parseGLSL(fragment_file);
        }

        return true;
    }

    const String ResourceLoader::parseGLSL(const String& res)
    {
        char *data = nullptr;
        int size = 0;
        FileUtils::loadShader(_data_path + res, data, size);
        if (data == nullptr) return "";

        return String(data);
    }

    bool ResourceLoader::load(CameraState* camera_state, const String& res)
    {
        char *data = nullptr;
        int size = 0;
        FileUtils::streamFromBinaryFile(_data_path + res, data, size);
        if (data == nullptr) return false;

        XMLDoc doc;
        doc.parseBuffer(data, size);
        if (doc.hasError())
        {
            cLog << "XML parsing error";
            return false;
        }

        XMLNode rootNode = doc.getRootNode();
        if (strcmp(rootNode.getName(), "Camera") != 0)
        {
            cLog << "Not a camera resource file";
            return false;
        }

        // Camera mode
        XMLNode node1 = rootNode.getFirstChild("CameraMode");
        if (!node1.isEmpty())
        {
            if (node1.getAttribute("mode") == 0x0)
            {
                cLog << "Missing Camera attribute 'mode'";
                return false;
            }
            String mode = node1.getAttribute("mode");
            if (mode == "ORTHOGRAPHIC") camera_state->setCameraMode(CameraState::CameraMode::ORTHOGONAL);
            else if (mode == "PERSPECTIVE") camera_state->setCameraMode(CameraState::CameraMode::PERSPECTIVE);
        }

        // View port
        node1 = rootNode.getFirstChild("ViewPort");
        if (!node1.isEmpty())
        {
            XMLNode node2 = node1.getFirstChild("Position");
            Var x = String(node1.getAttribute("x"));
            Var y = String(node1.getAttribute("y"));
            Var z = String(node1.getAttribute("z"));
            Vector3 position(x.toFloat(), y.toFloat(), z.toFloat());

            node2 = node1.getFirstChild("Center");
            x = String(node1.getAttribute("x"));
            y = String(node1.getAttribute("y"));
            z = String(node1.getAttribute("z"));
            Vector3 center(x.toFloat(), y.toFloat(), z.toFloat());

            node2 = node1.getFirstChild("Up");
            x = String(node1.getAttribute("x"));
            y = String(node1.getAttribute("y"));
            z = String(node1.getAttribute("z"));
            Vector3 up(x.toFloat(), y.toFloat(), z.toFloat());

            camera_state->setViewTransform(CameraState::CameraViewParas(position, center, up));
        }

        // View Transform
        node1 = rootNode.getFirstChild("ViewTransform");
        if (!node1.isEmpty())
        {
            Var x = String(node1.getAttribute("x"));
            Var y = String(node1.getAttribute("y"));
            Var w = String(node1.getAttribute("w"));
            Var h = String(node1.getAttribute("h"));

            camera_state->setViewPort(Vector4(x.toFloat(), y.toFloat(), w.toFloat(), h.toFloat()));
        }

        // View Transform
        node1 = rootNode.getFirstChild("ViewTransform");
        if (!node1.isEmpty())
        {
            Var x = String(node1.getAttribute("x"));
            Var y = String(node1.getAttribute("y"));
            Var w = String(node1.getAttribute("w"));
            Var h = String(node1.getAttribute("h"));

            camera_state->setViewPort(Vector4(x.toFloat(), y.toFloat(), w.toFloat(), h.toFloat()));
        }

        // Perspective Transform
        node1 = rootNode.getFirstChild("PerspectiveT");
        if (!node1.isEmpty())
        {
            Var fov = String(node1.getAttribute("fov"));
            Var aspect = String(node1.getAttribute("y"));
            Var znear = String(node1.getAttribute("znear"));
            Var zfar = String(node1.getAttribute("zfar"));

            camera_state->setPersProjectTransform(CameraState::CameraPersParas(fov.toFloat(), aspect.toFloat(), znear.toFloat(), zfar.toFloat()));
        }

        // Orthographic Transform
        node1 = rootNode.getFirstChild("OrthographicT");
        if (!node1.isEmpty())
        {
            Var left = String(node1.getAttribute("left"));
            Var right = String(node1.getAttribute("right"));
            Var bottom = String(node1.getAttribute("bottom"));
            Var top = String(node1.getAttribute("top"));
            Var znear = String(node1.getAttribute("znear"));
            Var zfar = String(node1.getAttribute("zfar"));

            camera_state->setOrthoProjectTransform(CameraState::CameraOrthoParas(left.toFloat(), right.toFloat(), 
                bottom.toFloat(), top.toFloat(), znear.toFloat(), zfar.toFloat()));

        }

        return true;
    }
}
