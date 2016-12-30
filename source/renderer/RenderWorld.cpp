#include "RenderWorld.h"

#include "common/Object.h"
#include "renderer/Device/RenderContext.h"
#include "renderer/Device/RenderDevice.h"
#include "renderer/resource/RenderMeshObject.h"
#include "renderer/resource/PipelineResource.h"

namespace te
{
    struct RenderQueueItem
    {
        RenderObject  *node;
        float      sortKey;
        uint32  type;

        RenderQueueItem() {}
        RenderQueueItem(float sortKey, RenderObject *node)
            : node(node), sortKey(sortKey) {}
    };

    typedef std::vector< RenderQueueItem > RenderQueue;

    void renderKernel(RenderWorld::RenderParams& params, RenderContext* rContext)
    {
        // culling, prepare RenderQueue
        RenderQueue rQueue;

        // iterate each object
        for (RenderQueueItem& rqItem : rQueue)
        {
            if (rqItem.type == RenderMeshObject::TYPE)
                ((RenderMeshObject*)rqItem.node)->render(rContext, params._camera, params._device);
        }
    }

    void RenderWorld::render(RenderParams& params)
    {
        RenderContext* renderContext = (params._device->newContext());

        // process pipeline config here
        for (PipelineStage& stage :params._pipelineRes->_stages)
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
                    break;
                }
            }
        }

        // send render job package to RenderDevice for real work
        params._device->dispatch(renderContext);
    }
}