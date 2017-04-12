#include "RenderResourceGenerator.h"

#include "RenderResourceContext.h"
#include "../Device/RenderDevice.h"

namespace te
{
    void allocResourceInternal(
        RenderResourceGenerator::RenderResourceParams& params,
        RenderResourceContext* rrc)
    {
        ResourceStreamQueue& rQueue = params._resourceQueue;

        // iterate each object
        for (auto rqItem : rQueue)
        {
            if (RenderResource::VERTEX_STREAM == rqItem.resType)
            {
                RenderResourceContext::Message allc_vs = {
                    RenderResourceContext::MessageType::ALLOC_VERTEX_BUFFER, (void*)rqItem.stream };
                rrc->messages().push_back(allc_vs);
            }
            else if (RenderResource::INDEX_STREAM == rqItem.resType)
            {
                RenderResourceContext::Message allc_is = {
                    RenderResourceContext::MessageType::ALLOC_INDEX_BUFFER, (void*)rqItem.stream };
                rrc->messages().push_back(allc_is);
            }
            else if (RenderResource::VERTEX_DECLARATION == rqItem.resType)
            {
                RenderResourceContext::Message allc_vd = {
                    RenderResourceContext::MessageType::ALLOC_VERTEX_DECLARATION, (void*)rqItem.stream };
                rrc->messages().push_back(allc_vd);
            }
            else
            {
                // TODO
            }
        }
    }

    void RenderResourceGenerator::allocResource(RenderResourceParams & params)
    {
        RenderResourceContext* rrc = (params._device->newResourceContext());
        allocResourceInternal(params, rrc);
        params._device->dispatch(rrc);
        params._device->releaseResourceContext(rrc);
    }
}