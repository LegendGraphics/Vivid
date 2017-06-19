#ifndef COMMON_PIPELINE_RESOURCE_H
#define COMMON_PIPELINE_RESOURCE_H

#include "vivid/base/Variant.h"
#include "vivid/common/Resource.h"

namespace te
{
    // attribute table
    struct PipelineAttribute
    {
        enum class RenderTarget
        {
            ID,
            DEPTHBUF,
            NCOLBUFS,
            FORMAT,
            WIDTH,

        };

        enum class Stage
        {
            ID,
            ENABLED,
            LINK
        };

        struct COMMAND
        {
            enum class SwitchTarget
            {
                TARGET
            };

            enum class BindBuffer
            {
                SAMPLER,
                SOURCERT,
                BUFINDEX
            };

            enum class UnbindBuffers
            {};

            enum class ClearTarget
            {
                DEPTHBUF,
                COLBUF0,
                COLBUF1,
                COLBUF2,
                COLBUF3,
                COLR,
                COLG,
                COLB,
                COLA
            };

            enum class DrawGeometry
            {
                CONTEXT,
                CLASS,
                ORDER
            };

            enum class DrawOverlays
            {
                CONTEXT
            };

            enum class DrawQuad
            {
                MATERIAL,
                CONTEXT
            };

            enum class DoForwardLightLoop
            {
                CLASS,
                CONTEXT,
                ORDER,
                NOSHADOWS
            };

            enum class DoDeferredLightLoop
            {
                CONTEXT
            };

            enum class SetUniform
            {
                MATERIAL,
                UNIFORM,
                A,
                B,
                C,
                D
            };
        };
    };

    enum class PipelineCommandType
    {
        SwitchTarget,
        ClearTarget,
        SetTarget,
        BindBuffer,
        UnbindBuffers,
        DrawGeometry,
        DrawOverlays,
        DrawQuad,
        DoForwardLightLoop,
        DoDeferredLightLoop,
        SetUniform
    };

    struct PipelineCommand
    {
        using Paras = std::vector<Var>; // the order of parameters is determined by format definition

        Paras                   paras;
        PipelineCommandType     command;
        

        PipelineCommand(PipelineCommandType command)
        {
            this->command = command;
        }
    };

    struct PipelineStage
    {
        using Commands = std::vector<PipelineCommand>;

        String          id;
        bool            enabled;
        Commands        commands;
    };

    using PipelineStages = std::vector<PipelineStage>;

    class Pipeline : public Resource
    {
    public:
        Pipeline();
        virtual ~Pipeline() = default;

        friend class ResourceLoader;

        bool load(const String & res);
        void unload();

        PipelineStages& getStages() { return _stages; }

    protected:
        PipelineStages  _stages;
    };

    using PipelinePtr = RefPtr<Pipeline>;

    class PipelineManager : public ResourceManager
    {
    public:
        PipelineManager();
        ~PipelineManager();

        ResourceHandle create(const String& res);

        PipelinePtr   getPipeline(ResourceHandle handle);
        PipelinePtr   getPipeline(const String& res);
    };
}

#endif // COMMON_PIPELINE_RESOURCE_H
