#ifndef RENDERER_PIPELINERESOURCE_H
#define RENDERER_PIPELINERESOURCE_H

#include "utXML.h"

#include "RenderResource.h"
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

    class PipeCmdParam
    {
    public:
        PipeCmdParam() : _string(0x0) { _basic.ptr = 0x0; }
        PipeCmdParam(const PipeCmdParam &copy)
            : _basic(copy._basic), _string(0x0), _resource(copy._resource)
        {
            if (copy._string) setString(copy._string->c_str());
        }
        ~PipeCmdParam() { delete _string; }

        float getFloat() { return _basic.f; }
        int getInt() { return _basic.i; }
        bool getBool() { return _basic.b; }
        void *getPtr() { return _basic.ptr; }
        const char *getString() { return _string ? _string->c_str() : 0x0; }
        Resource *getResource() { return _resource; }

        void setFloat(float f) { _basic.f = f; }
        void setInt(int i) { _basic.i = i; }
        void setBool(bool b) { _basic.b = b; }
        void setPtr(void *ptr) { _basic.ptr = ptr; }
        void setString(const char *str) { _string = new std::string(str); }
        void setResource(Resource *resource) { _resource = resource; }

    protected:
        union BasicType
        {
            float  f;
            int    i;
            bool   b;
            void   *ptr;
        };

        BasicType      _basic;
        std::string    *_string;
        Resource*      _resource;
    };

    struct PipelineCommand
    {
        enum List : uint8
        {
            SwitchTarget,
            ClearTarget,
            BindBuffer,
            UnbindBuffers,
            DrawGeometry, 
            DrawOverlays,
            DrawQuad,
            SetTarget,
            DoForwardLightLoop,
            DoDeferredLightLoop,
            SetUniform
        }; ///< This is used for pipeline configuration set from json/xml files
        ///< They are different from context command
        List command;
        std::vector<PipeCmdParam> params;

        PipelineCommand(List    command)
        {
            this->command = command;
        }
    };

    struct PipelineStage
    {
        std::string     id;
        bool            enabled;
        std::vector<PipelineCommand> commands;
    };

    /*class PipelineResource : public RenderResource
    {
    public:
        static RenderResource::Type TYPE;

        PipelineResource();
        ~PipelineResource();

    private:
        std::vector<PipelineStage> _stages;

        friend class RenderWorld;
    };*/

    struct RenderTarget
    {
        std::string           id;
        uint32                numColBufs;
       // TextureFormats::List  format;
        uint32                width, height;
        uint32                samples;
        float                 scale;  // Scale factor for FB width and height
        bool                  hasDepthBuf;
        uint32                rendBuf;

        RenderTarget()
        {
            hasDepthBuf = false;
            numColBufs = 0;
            rendBuf = 0;
        }
    };

    class PipelineResource : public Resource
    {
    public:
        using PipelineStages = std::vector< PipelineStage >;

        PipelineResource();
        ~PipelineResource();

        void initDefault();
        void release();
        bool load(const std::string& res);
        void unload() {}
        void resize(uint32 width, uint32 height);

        bool getRenderTargetData(const std::string &target, int bufIndex, int *width, int *height,
            int *compCount, void *dataBuffer, int bufferSize);

        PipelineStages& getStages() { return _stages; }

    private:
        const std::string parseStage(XMLNode &node, PipelineStage &stage);

        void addRenderTarget(const std::string &id, bool depthBuffer, uint32 numBuffers,
            /*TextureFormats::List format,*/ uint32 samples,
            uint32 width, uint32 height, float scale);
        RenderTarget* findRenderTarget(const std::string &id);
        bool createRenderTargets();
        void releaseRenderTargets();

    private:
        std::vector< RenderTarget >   _renderTargets;
        std::vector< PipelineStage >  _stages;
        uint32                        _baseWidth, _baseHeight;
    };
}

#endif
