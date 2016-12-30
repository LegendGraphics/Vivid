#ifndef RENDERER_PIPELINERESOURCE_H
#define RENDERER_PIPELINERESOURCE_H

#include "RenderResource.h"

namespace te
{
    class PipeCmdParam
    {
    public:
        union BasicType
        {
            float f;
            int   i;
            bool  b;
            void* ptr;
        };

        BasicType _basic;
    };

    struct PipelineCommand
    {
        enum List : uint8
        {
            ClearTarget,
            DrawGeometry,
            SetTarget
        }; ///< This is used for pipeline configuration set from json/xml files
        ///< They are different from context command
        List command;
        std::vector<PipeCmdParam> params;
    };

    struct PipelineStage
    {
        std::vector<PipelineCommand> commands;
    };

    class PipelineResource : public RenderResource
    {
    public:
        static RenderResource::Type TYPE;

        PipelineResource();
        ~PipelineResource();

    private:
        std::vector<PipelineStage> _stages;

        friend class RenderWorld;
    };
}

#endif
