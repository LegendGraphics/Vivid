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
        Mesh,
        Skeleton,
        Animation,
        Material,
        Code,
        Shader,
        Texture,
        ParticleEffect,
        Pipeline
    };

    using ResourceHandle = unsigned long;

    class Resource /*: public Object*/
    {
    public:
        Resource();
      //  Resource(const Resource& resource, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Resource();
        
      //  OBJECT_META_FUNCTION(Resource);

        virtual bool load(const std::string& res);
        virtual void unload();

        ResourceType getType() const { return _type; }
        ResourceHandle getResourceHandle() const { return _handle; }

    protected:
        ResourceType    _type;
        ResourceHandle  _handle;
    };

    class ResourceManager /*: public Object*/
    {
    public:
        ResourceManager(ResourceType type);
//        ResourceManager(const ResourceManager& res_mgr, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~ResourceManager();

//        OBJECT_META_FUNCTION(ResourceManager);

        ResourceType getType() const { return _type; }

        virtual bool create(const std::string& res) = 0;
        
        ResourceHandle getNextResHandle();

        void add(Resource* resource);
        void remove(ResourceHandle handle);
        bool has(Resource* resource);
        bool has(ResourceHandle handle);
        
    protected:
        std::unordered_map<ResourceHandle, Resource*> _resources;
        ResourceType    _type;
        ResourceHandle  _next_handle;
    };

    class ResourceMap /*: public Object*/
    {
    public:
        ResourceMap();
        //ResourceMap(const ResourceMap& res_map, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~ResourceMap();

        //OBJECT_META_FUNCTION(ResourceMap);
        
        void registerResource(ResourceType type);
        void unregisterResource(ResourceType type);
        bool hasRegistered(ResourceType type);

    protected:
        std::unordered_map<ResourceType, ResourceManager*>    _res_map;
    };
}

#endif // COMMON_RESOURCE_H