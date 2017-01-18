#ifndef COMMON_RESOURCE_H
#define COMMON_RESOURCE_H

#include <vector>
#include <unordered_map>

#include "common/Object.h"
#include "base/RefPtr.hpp"

namespace te
{
    enum class ResourceType
    {
        Undefined,
        SceneGraph,
        Geometry,
        Animation,
        Material,
        Code,
        Shader,
        Texture,
        ParticleEffect,
        Pipeline
    };

    using ResourceHandle = int;

    class Resource : public Object
    {
    public:
        Resource(ResourceType type);
        Resource(const Resource& resource, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Resource();
        
        OBJECT_META_FUNCTION(Resource);

        virtual void release();
        virtual bool load(const char *data, int size);
        void unload();

        ResourceType getType() const { return _type; }
        bool isLoaded() const { return _loaded; }
        ResourceHandle getResourceHandle() const { return _handle; }
        void setResourceHandle(ResourceHandle handle);

    protected:
        ResourceType    _type;
        ResourceHandle  _handle;
        bool            _loaded;
    };

    class ResoureManager : public Object
    {
    public:
        ResoureManager(ResourceType type);
        ResoureManager(const ResoureManager& res_mgr, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~ResoureManager();

        OBJECT_META_FUNCTION(ResoureManager);

        ResourceType getType() const { return _type; }

        void addResource(Resource* resource);
        void removeResource(ResourceHandle handle);
        bool hasResource(Resource* resource);
        bool hasResource(ResourceHandle handle);
        
    protected:
        std::vector<RefPtr<Resource>> _resources;
        ResourceType    _type;
    };

    class ResourceMap : public Object
    {
    public:
        ResourceMap();
        ResourceMap(const ResourceMap& res_map, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~ResourceMap();

        OBJECT_META_FUNCTION(ResourceMap);
        
        void registerResource(ResourceType type);
        void unregisterResource(ResourceType type);
        bool hasRegistered(ResourceType type);

    protected:
        std::unordered_map<ResourceType, RefPtr<ResoureManager>>    _res_map;
    };
}

#endif // COMMON_RESOURCE_H