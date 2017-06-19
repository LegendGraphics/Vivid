#include "vivid/renderer/RenderWorld.h"

#include "vivid/common/Pipeline.h"
#include "vivid/renderer/device/CommandStream.h"
#include "vivid/renderer/device/RenderContext.h"
#include "vivid/renderer/device/RenderDevice.h"

namespace vivid
{
    void RenderWorld::renderKernel(StateStream& stream, RenderParams& params, RenderContext* render_context)
    {
        // culling, prepare RenderQueue

        // iterate each object
        for (StateStreamMsg* msg : stream)
            msg->process(render_context, nullptr, this);
    }

    RenderObject::Type RenderWorld::TYPE = RenderObject::NOT_INITIALIZED;

    RenderWorld::RenderWorld() : RenderObject(TYPE)
    {
    }

    RenderWorld::~RenderWorld()
    {
    }

    // rendering image
    void RenderWorld::render(StateStream& stream, RenderParams& params)
    {
        RenderContext* render_context = (params.device->newContext());
        render_context->_camera = params.camera;

        // process pipeline config here
        for (PipelineStage& stage : params.pipeline->getStages())
        {
            for (PipelineCommand& pc : stage.commands)
            {
                switch (pc.command)
                {
                case PipelineCommandType::SetTarget:
                    break;
                case PipelineCommandType::DrawGeometry:
                    // generate render job package (commands) into RenderContext
                    // separate this from real job will benefit for multi-thread
                    renderKernel(stream, params, render_context);
                    break;
                case PipelineCommandType::ClearTarget:
                    command_stream::ClearCmdStream* ccs = new command_stream::ClearCmdStream;
                    ccs->clear_color = pc.paras[1].toBool() || pc.paras[2].toBool()
                        || pc.paras[3].toBool() || pc.paras[4].toBool();
                    ccs->clear_depth = pc.paras[0].toBool();
                    ccs->color_rgba[0] = pc.paras[5].toFloat();
                    ccs->color_rgba[1] = pc.paras[6].toFloat();
                    ccs->color_rgba[2] = pc.paras[7].toFloat();
                    ccs->color_rgba[3] = pc.paras[8].toFloat();
                    ccs->depth = 1.f;
                    RenderContext::Command clear_target = { 0, (void*)ccs, command_stream::CommandType::CLEAR };
                    render_context->commands().push_back(clear_target);
                    break;
                }
            }
        }

        // send render job package to RenderDevice for real work
        params.device->dispatch(render_context);
        params.device->releaseContext(render_context);
    }

    RenderObject* RenderWorld::getRenderObject(Handle handle)
    {
        if (!_objects.has(handle))
            return nullptr;
        else
            return _objects.getPtr(handle);
    }

    Handle RenderWorld::addRenderObject(RenderObject* ro)
    {
        return _objects.add(ro);
    }

    // updating resource status 
    void RenderWorld::update(StateStream& stream, RenderDevice* device)
    {
        RenderResourceContext* rrc = device->newResourceContext();

        for (StateStreamMsg* msg : stream)
            msg->process(nullptr, rrc, this);

        device->dispatch(rrc);
        device->releaseResourceContext(rrc);
    }

}