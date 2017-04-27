#ifndef COMMON_PIPELINE_RESOURCE_H
#define COMMON_PIPELINE_RESOURCE_H

#include "base/Variant.h"
#include "common/Resource.h"

namespace te
{
    struct RenderingOrder
    {
        enum List
        {
            None = 0,
            FrontToBack,
            BackToFront,
            StateChanges
        };
    };

    //class PipeCmdParam
    //{
    //public:
    //    PipeCmdParam() : _string(0x0) { _basic.ptr = 0x0; }
    //    PipeCmdParam(const PipeCmdParam &copy)
    //        : _basic(copy._basic), _string(0x0), _resource(copy._resource)
    //    {
    //        if (copy._string) setString(copy._string->c_str());
    //    }
    //    ~PipeCmdParam() { delete _string; }

    //    float getFloat() { return _basic.f; }
    //    int getInt() { return _basic.i; }
    //    bool getBool() { return _basic.b; }
    //    void *getPtr() { return _basic.ptr; }
    //    const char *getString() { return _string ? _string->c_str() : 0x0; }
    //    Resource *getResource() { return _resource; }

    //    void setFloat(float f) { _basic.f = f; }
    //    void setInt(int i) { _basic.i = i; }
    //    void setBool(bool b) { _basic.b = b; }
    //    void setPtr(void *ptr) { _basic.ptr = ptr; }
    //    void setString(const char *str) { _string = new String(str); }
    //    void setResource(Resource *resource) { _resource = resource; }

    //protected:
    //    union BasicType
    //    {
    //        float  f;
    //        int    i;
    //        bool   b;
    //        void   *ptr;
    //    };

    //    BasicType      _basic;
    //    String    *_string;
    //    Resource*      _resource;
    //};
    //

    //class PipelineResource : public Resource
    //{
    //public:
    //    using PipelineStages = std::vector< PipelineStage >;

    //    PipelineResource();
    //    ~PipelineResource();

    //    void initDefault();
    //    void release();
    //    bool load(const String& res);
    //    void unload() {}
    //    void resize(uint32 width, uint32 height);

    //    bool getRenderTargetData(const String &target, int bufIndex, int *width, int *height,
    //        int *compCount, void *dataBuffer, int bufferSize);

    //    PipelineStages& getStages() { return _stages; }

    //private:
    //    const String parseStage(XMLNode &node, PipelineStage &stage);

    //private:
    //    std::vector< PipelineStage >  _stages;
    //};


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
