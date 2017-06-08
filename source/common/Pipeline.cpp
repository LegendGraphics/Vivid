#include "common/Pipeline.h"

#include "io/ResourceLoader.h"

namespace te
{
    Pipeline::Pipeline()
    {
    }

    bool Pipeline::load(const String & res)
    {
        return ResourceLoader::load(this, res);
    }

    void Pipeline::unload()
    {

    }

    PipelineManager::PipelineManager()
        :ResourceManager(ResourceType::Pipeline)
    {}

    PipelineManager::~PipelineManager() {}

    ResourceHandle PipelineManager::create(const String& res)
    {
        if (ResourceHandle handle = getResourceHandle(res)) return handle;
        else
        {
            PipelinePtr pipeline = new Pipeline;
            if (pipeline->load(res))
            {
                pipeline->descriptor(buildDescriptor(res));
                add(pipeline.get());
                return getResourceHandle(res);
            }
            else return 0;
        }
    }

    PipelinePtr PipelineManager::getPipeline(ResourceHandle handle)
    {
        if (has(handle)) return dynamic_cast_ptr<Resource, Pipeline>(getResourcePtr(handle));
        else return nullptr;
    }

    PipelinePtr PipelineManager::getPipeline(const String& res)
    {
        return getPipeline(getResourceHandle(res));
    }


}