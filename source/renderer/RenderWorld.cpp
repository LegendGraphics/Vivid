#include "RenderWorld.h"

#include "common/Clone.h"
#include "renderer/Device/RenderContext.h"
#include "renderer/Device/RenderDevice.h"
#include "renderer/resource/RenderMeshObject.h"
#include "renderer/resource/PipelineResource.h"

#include "math/Vector3.h"

namespace te
{
    void renderKernel(RenderWorld::RenderParams& params, RenderContext* rContext)
    {
        // culling, prepare RenderQueue
        RenderQueue& rQueue = params._renderQueue;

        // iterate each object
        for (RenderQueueItem& rqItem : rQueue)
        {
            if (rqItem.node->type == RenderMeshObject::TYPE)
                ((RenderMeshObject*)rqItem.node)->render(rContext, params._camera, params._device);
        }
    }

    RenderObject::Type RenderWorld::TYPE = RenderObject::NOT_INITIALIZED;

    RenderWorld::RenderWorld() : RenderObject(TYPE)
    {
    }

    RenderWorld::~RenderWorld()
    {
    }

    void RenderWorld::render(RenderParams& params)
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
                    renderKernel(params, renderContext);
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

    void RenderWorld::update()
    {
    }
}