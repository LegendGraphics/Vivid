#include "PipelineResource.h"

#include "io/FileUtils.h"

namespace te
{
    /*RenderResource::Type PipelineResource::TYPE = RenderResource::NOT_INITIALIZED;
    PipelineResource::PipelineResource()
    {
    }
    PipelineResource::~PipelineResource()
    {
    }*/
    PipelineResource::PipelineResource()
        :Resource(ResourceType::Pipeline)
    {
        initDefault();
    }


    PipelineResource::~PipelineResource()
    {
        release();
    }


    void PipelineResource::initDefault()
    {
        _baseWidth = 320; _baseHeight = 240;
    }


    void PipelineResource::release()
    {
        releaseRenderTargets();

        _renderTargets.clear();
        _stages.clear();
    }

    const std::string PipelineResource::parseStage(XMLNode &node, PipelineStage &stage)
    {
        stage.id = node.getAttribute("id", "");

        if (_stricmp(node.getAttribute("enabled", "true"), "false") == 0 ||
            _stricmp(node.getAttribute("enabled", "1"), "0") == 0)
            stage.enabled = false;
        else
            stage.enabled = true;

        /*if (strcmp(node.getAttribute("link", ""), "") != 0)
        {
            uint32 mat = Modules::resMan().addResource(
                ResourceTypes::Material, node.getAttribute("link"), 0, false);
            stage.matLink = (MaterialResource *)Modules::resMan().resolveResHandle(mat);
        }*/

        stage.commands.reserve(node.countChildNodes());

        // Parse commands
        XMLNode node1 = node.getFirstChild();
        while (!node1.isEmpty())
        {
            if (strcmp(node1.getName(), "SwitchTarget") == 0)
            {
                if (!node1.getAttribute("target")) return "Missing SwitchTarget attribute 'target'";

                void *renderTarget = 0x0;
                if (strcmp(node1.getAttribute("target"), "") != 0)
                {
                    renderTarget = findRenderTarget(node1.getAttribute("target"));
                    if (!renderTarget) return "Reference to undefined render target in SwitchTarget";
                }

                stage.commands.push_back(PipelineCommand(PipelineCommand::SwitchTarget));
                stage.commands.back().params.resize(1);
                stage.commands.back().params[0].setPtr(renderTarget);
            }
            else if (strcmp(node1.getName(), "BindBuffer") == 0)
            {
                if (!node1.getAttribute("sampler") || !node1.getAttribute("sourceRT") || !node1.getAttribute("bufIndex"))
                    return "Missing BindBuffer attribute";

                void *renderTarget = findRenderTarget(node1.getAttribute("sourceRT"));
                if (!renderTarget) return "Reference to undefined render target in BindBuffer";

                stage.commands.push_back(PipelineCommand(PipelineCommand::BindBuffer));
                std::vector< PipeCmdParam > &params = stage.commands.back().params;
                params.resize(3);
                params[0].setPtr(renderTarget);
                params[1].setString(node1.getAttribute("sampler"));
                params[2].setInt(atoi(node1.getAttribute("bufIndex")));
            }
            else if (strcmp(node1.getName(), "UnbindBuffers") == 0)
            {
                stage.commands.push_back(PipelineCommand(PipelineCommand::UnbindBuffers));
            }
            else if (strcmp(node1.getName(), "ClearTarget") == 0)
            {
                stage.commands.push_back(PipelineCommand(PipelineCommand::ClearTarget));
                std::vector< PipeCmdParam > &params = stage.commands.back().params;
                params.resize(9);
                params[0].setBool(false);
                params[1].setBool(false);
                params[2].setBool(false);
                params[3].setBool(false);
                params[4].setBool(false);
                params[5].setFloat((float)atof(node1.getAttribute("col_R", "0")));
                params[6].setFloat((float)atof(node1.getAttribute("col_G", "0")));
                params[7].setFloat((float)atof(node1.getAttribute("col_B", "0")));
                params[8].setFloat((float)atof(node1.getAttribute("col_A", "0")));

                if (_stricmp(node1.getAttribute("depthBuf", "false"), "true") == 0 ||
                    _stricmp(node1.getAttribute("depthBuf", "0"), "1") == 0)
                {
                    params[0].setBool(true);
                }
                if (_stricmp(node1.getAttribute("colBuf0", "false"), "true") == 0 ||
                    _stricmp(node1.getAttribute("colBuf0", "0"), "1") == 0)
                {
                    params[1].setBool(true);
                }
                if (_stricmp(node1.getAttribute("colBuf1", "false"), "true") == 0 ||
                    _stricmp(node1.getAttribute("colBuf1", "0"), "1") == 0)
                {
                    params[2].setBool(true);
                }
                if (_stricmp(node1.getAttribute("colBuf2", "false"), "true") == 0 ||
                    _stricmp(node1.getAttribute("colBuf2", "0"), "1") == 0)
                {
                    params[3].setBool(true);
                }
                if (_stricmp(node1.getAttribute("colBuf3", "false"), "true") == 0 ||
                    _stricmp(node1.getAttribute("colBuf3", "0"), "1") == 0)
                {
                    params[4].setBool(true);
                }
            }
            else if (strcmp(node1.getName(), "DrawGeometry") == 0)
            {
                if (!node1.getAttribute("context")) return "Missing DrawGeometry attribute 'context'";

                const char *orderStr = node1.getAttribute("order", "");
                int order = RenderingOrder::StateChanges;
                if (_stricmp(orderStr, "FRONT_TO_BACK") == 0) order = RenderingOrder::FrontToBack;
                else if (_stricmp(orderStr, "BACK_TO_FRONT") == 0) order = RenderingOrder::BackToFront;
                else if (_stricmp(orderStr, "NONE") == 0) order = RenderingOrder::None;

                stage.commands.push_back(PipelineCommand(PipelineCommand::DrawGeometry));
                std::vector< PipeCmdParam > &params = stage.commands.back().params;
                params.resize(3);
                params[0].setString(node1.getAttribute("context"));
                params[1].setString(node1.getAttribute("class", ""));
                params[2].setInt(order);
            }
            else if (strcmp(node1.getName(), "DrawOverlays") == 0)
            {
                if (!node1.getAttribute("context")) return "Missing DrawOverlays attribute 'context'";

                stage.commands.push_back(PipelineCommand(PipelineCommand::DrawOverlays));
                std::vector< PipeCmdParam > &params = stage.commands.back().params;
                params.resize(1);
                params[0].setString(node1.getAttribute("context"));
            }
            else if (strcmp(node1.getName(), "DrawQuad") == 0)
            {
                if (!node1.getAttribute("material")) return "Missing DrawQuad attribute 'material'";
                if (!node1.getAttribute("context")) return "Missing DrawQuad attribute 'context'";

                /*uint32 matRes = Modules::resMan().addResource(
                    ResourceTypes::Material, node1.getAttribute("material"), 0, false);*/

                stage.commands.push_back(PipelineCommand(PipelineCommand::DrawQuad));
                std::vector< PipeCmdParam > &params = stage.commands.back().params;
                params.resize(2);
                //params[0].setResource(Modules::resMan().resolveResHandle(matRes));
                params[1].setString(node1.getAttribute("context"));
            }
            else if (strcmp(node1.getName(), "DoForwardLightLoop") == 0)
            {
                const char *orderStr = node1.getAttribute("order", "");
                int order = RenderingOrder::StateChanges;
                if (_stricmp(orderStr, "FRONT_TO_BACK") == 0) order = RenderingOrder::FrontToBack;
                else if (_stricmp(orderStr, "BACK_TO_FRONT") == 0) order = RenderingOrder::BackToFront;
                else if (_stricmp(orderStr, "NONE") == 0) order = RenderingOrder::None;

                stage.commands.push_back(PipelineCommand(PipelineCommand::DoForwardLightLoop));
                std::vector< PipeCmdParam > &params = stage.commands.back().params;
                params.resize(4);
                params[0].setString(node1.getAttribute("context", ""));
                params[1].setString(node1.getAttribute("class", ""));
                params[2].setBool(_stricmp(node1.getAttribute("noShadows", "false"), "true") == 0);
                params[3].setInt(order);
            }
            else if (strcmp(node1.getName(), "DoDeferredLightLoop") == 0)
            {
                stage.commands.push_back(PipelineCommand(PipelineCommand::DoDeferredLightLoop));
                std::vector< PipeCmdParam > &params = stage.commands.back().params;
                params.resize(2);
                params[0].setString(node1.getAttribute("context", ""));
                params[1].setBool(_stricmp(node1.getAttribute("noShadows", "false"), "true") == 0);
            }
            else if (strcmp(node1.getName(), "SetUniform") == 0)
            {
                if (!node1.getAttribute("material")) return "Missing SetUniform attribute 'material'";
                if (!node1.getAttribute("uniform")) return "Missing SetUniform attribute 'uniform'";

                /*uint32 matRes = Modules::resMan().addResource(
                    ResourceTypes::Material, node1.getAttribute("material"), 0, false);*/

                stage.commands.push_back(PipelineCommand(PipelineCommand::SetUniform));
                std::vector< PipeCmdParam > &params = stage.commands.back().params;
                params.resize(6);
                //params[0].setResource(Modules::resMan().resolveResHandle(matRes));
                params[1].setString(node1.getAttribute("uniform"));
                params[2].setFloat((float)atof(node1.getAttribute("a", "0")));
                params[3].setFloat((float)atof(node1.getAttribute("b", "0")));
                params[4].setFloat((float)atof(node1.getAttribute("c", "0")));
                params[5].setFloat((float)atof(node1.getAttribute("d", "0")));
            }

            node1 = node1.getNextSibling();
        }

        return "";
    }


    void PipelineResource::addRenderTarget(const std::string &id, bool depthBuf, uint32 numColBufs,
        /*TextureFormats::List format,*/ uint32 samples,
        uint32 width, uint32 height, float scale)
    {
        RenderTarget rt;

        rt.id = id;
        rt.hasDepthBuf = depthBuf;
        rt.numColBufs = numColBufs;
       // rt.format = format;
        rt.samples = samples;
        rt.width = width;
        rt.height = height;
        rt.scale = scale;

        _renderTargets.push_back(rt);
    }


    RenderTarget* PipelineResource::findRenderTarget(const std::string &id)
    {
        if (id == "") return nullptr;

        for (uint32 i = 0; i < _renderTargets.size(); ++i)
        {
            if (_renderTargets[i].id == id)
            {
                return &_renderTargets[i];
            }
        }

        return nullptr;
    }


    bool PipelineResource::createRenderTargets()
    {
        for (uint32 i = 0; i < _renderTargets.size(); ++i)
        {
            RenderTarget &rt = _renderTargets[i];

            uint32 width = int(rt.width * rt.scale), height = int(rt.height * rt.scale);
            if (width == 0) width = int(_baseWidth * rt.scale);
            if (height == 0) height = int(_baseHeight * rt.scale);

            /*rt.rendBuf = gRDI->createRenderBuffer(
                width, height, rt.format, rt.hasDepthBuf, rt.numColBufs, rt.samples);*/
            if (rt.rendBuf == 0) return false;
        }

        return true;
    }


    void PipelineResource::releaseRenderTargets()
    {
        for (uint32 i = 0; i < _renderTargets.size(); ++i)
        {
            RenderTarget &rt = _renderTargets[i];
            if (rt.rendBuf)
                /*gRDI->destroyRenderBuffer(rt.rendBuf)*/;
        }
    }


    bool PipelineResource::load(const std::string& res)
    {
        if (!Resource::load(res)) return false;

        char *data = nullptr;
        int size = 0;

        streamFromBinaryFile(res, data, size);

        XMLDoc doc;
        doc.parseBuffer(data, size);
        if (doc.hasError())
            /*return raiseError("XML parsing error")*/;

        XMLNode rootNode = doc.getRootNode();
        if (strcmp(rootNode.getName(), "Pipeline") != 0)
            /*return raiseError("Not a pipeline resource file")*/;

        // Parse setup
        XMLNode node1 = rootNode.getFirstChild("Setup");
        if (!node1.isEmpty())
        {
            XMLNode node2 = node1.getFirstChild("RenderTarget");
            while (!node2.isEmpty())
            {
                if (!node2.getAttribute("id")) /*return raiseError("Missing RenderTarget attribute 'id'")*/;
                std::string id = node2.getAttribute("id");

                if (!node2.getAttribute("depthBuf")) /*return raiseError("Missing RenderTarget attribute 'depthBuf'")*/;
                bool depth = false;
                if (_stricmp(node2.getAttribute("depthBuf"), "true") == 0) depth = true;

                if (!node2.getAttribute("numColBufs")) /*return raiseError("Missing RenderTarget attribute 'numColBufs'")*/;
                uint32 numBuffers = atoi(node2.getAttribute("numColBufs"));

                /*TextureFormats::List format = TextureFormats::BGRA8;
                if (node2.getAttribute("format") != 0x0)
                {
                    if (_stricmp(node2.getAttribute("format"), "RGBA8") == 0)
                        format = TextureFormats::BGRA8;
                    else if (_stricmp(node2.getAttribute("format"), "RGBA16F") == 0)
                        format = TextureFormats::RGBA16F;
                    else if (_stricmp(node2.getAttribute("format"), "RGBA32F") == 0)
                        format = TextureFormats::RGBA32F;
                    else return raiseError("Unknown RenderTarget format");
                }*/

                int maxSamples = atoi(node2.getAttribute("maxSamples", "0"));

                uint32 width = atoi(node2.getAttribute("width", "0"));
                uint32 height = atoi(node2.getAttribute("height", "0"));
                float scale = (float)atof(node2.getAttribute("scale", "1"));

                /*addRenderTarget(id, depth, numBuffers, format,
                    std::min(maxSamples, Modules::config().sampleCount), width, height, scale);*/

                node2 = node2.getNextSibling("RenderTarget");
            }
        }

        // Parse commands
        node1 = rootNode.getFirstChild("CommandQueue");
        if (!node1.isEmpty())
        {
            _stages.reserve(node1.countChildNodes("Stage"));

            XMLNode node2 = node1.getFirstChild("Stage");
            while (!node2.isEmpty())
            {
                _stages.push_back(PipelineStage());
                std::string errorMsg = parseStage(node2, _stages.back());
                if (errorMsg != "")
                    /*return raiseError("Error in stage '" + _stages.back().id + "': " + errorMsg)*/;

                node2 = node2.getNextSibling("Stage");
            }
        }

        // Create render targets
        if (!createRenderTargets())
        {
            /*return raiseError("Failed to create render target");*/
        }

        return true;
    }


    void PipelineResource::resize(uint32 width, uint32 height)
    {
        _baseWidth = width;
        _baseHeight = height;
        // Recreate render targets
        releaseRenderTargets();
        createRenderTargets();
    }

    bool PipelineResource::getRenderTargetData(const std::string &target, int bufIndex, int *width, int *height,
        int *compCount, void *dataBuffer, int bufferSize)
    {
        uint32 rbObj = 0;
        if (target != "")
        {
            RenderTarget *rt = findRenderTarget(target);
            if (rt == 0x0) return false;
            else rbObj = rt->rendBuf;
        }

        return true;
        /*return gRDI->getRenderBufferData(
            rbObj, bufIndex, width, height, compCount, dataBuffer, bufferSize);*/
    }
}