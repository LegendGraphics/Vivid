#include "RenderWorld.h"

#include "common/Clone.h"
#include "renderer/Device/RenderContext.h"
#include "renderer/Device/RenderDevice.h"
#include "renderer/resource/RenderMeshObject.h"
#include "renderer/resource/PipelineResource.h"

#include "math/Vector3.h"

namespace te
{
    void RenderWorld::renderKernel(StateStream& stream, RenderParams& params, RenderContext* rContext)
    {
        // culling, prepare RenderQueue

        // iterate each object
        for (StreamMsg* msg : stream)
        {
            StreamMsg::MsgType type = msg->getMsgType();
            if (StreamMsg::RENDER == type)
            {
                Handle* handle = msg->getHandle();
                RenderObject* ro = _objects.getPtr((*handle));
                msg->process(ro, rContext, nullptr);
            }
        }
    }

    RenderObject::Type RenderWorld::TYPE = RenderObject::NOT_INITIALIZED;

    RenderWorld::RenderWorld() : RenderObject(TYPE)
    {
    }

    RenderWorld::~RenderWorld()
    {
    }

    void RenderWorld::render(StateStream& stream, RenderParams& params)
    {
        RenderContext* renderContext = (params._device->newContext());
        renderContext->_camera = params._camera;

        // process pipeline config here
        for (PipelineStage& stage :params._pipelineRes->getStages())
        {
            for (PipelineCommand& pc : stage.commands)
            {
                switch (pc.command)
                {
                case PipelineCommand::List::SetTarget:
                    break;
                case PipelineCommand::List::DrawGeometry:
                    // generate render job package (commands) into RenderContext
                    // separate this from real job will benefit for multi-thread
                    renderKernel(stream, params, renderContext);
                    break;
                case PipelineCommand::List::ClearTarget:
                    RenderContext::ClearCmdStream* ccs = new RenderContext::ClearCmdStream;
                    ccs->clearColor = pc.params[1].getBool() || pc.params[2].getBool()
                        || pc.params[3].getBool() || pc.params[4].getBool();
                    ccs->clearDepth = pc.params[0].getBool();
                    ccs->colorRGBA[0] = pc.params[5].getFloat();
                    ccs->colorRGBA[1] = pc.params[6].getFloat();
                    ccs->colorRGBA[2] = pc.params[7].getFloat();
                    ccs->colorRGBA[3] = pc.params[8].getFloat();
                    ccs->depth = 1.f;
                    RenderContext::Command clearTarget = { 0, (void*)ccs, RenderContext::CommandType::CLEAR };
                    renderContext->commands().push_back(clearTarget);
                    break;
                }
            }
        }

        // send render job package to RenderDevice for real work
        params._device->dispatch(renderContext);
        params._device->releaseContext(renderContext);
    }

    void RenderWorld::update(StateStream& stream, RenderDevice* device)
    {
        RenderResourceContext* rrc = device->newResourceContext();

        for (StreamMsg* msg : stream)
        {
            StreamMsg::MsgType type = msg->getMsgType();
            if (StreamMsg::CREATE == type)
            {
                Handle* handle = msg->getHandle();
                RenderObject* ro = nullptr;
                msg->process(ro, nullptr, rrc);
                (*handle) = _objects.add(ro);
            }
            else if (StreamMsg::UPDATE == type)
            {
                Handle* handle = msg->getHandle();
                RenderObject* ro = _objects.getPtr((*handle));
                msg->process(ro, nullptr, rrc);
            }
        }

        device->dispatch(rrc);
        device->releaseResourceContext(rrc);
    }
}