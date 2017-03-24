#ifndef COMMON_RESOURCE_H
#define COMMON_RESOURCE_H

#include <vector>
#include <unordered_map>

#include "common/Object.h"
#include "base/RefPtr.hpp"

namespace te
{
    enum class ResourceType : unsigned long
    {
        Undefined =         (0 << 8),
        SceneGraph =        (1 << 8),
        Mesh =              (2 << 8),
        Skeleton =          (3 << 8),
        Animation =         (4 << 8),
        Material =          (5 << 8),
        Code =              (6 << 8),
        Shader =            (7 << 8),
        Texture =           (8 << 8),
        ParticleEffect =    (9 << 8),
        Pipeline =         (10 << 8)
    };

    //enum ResourceType
    //{
    //    Mesh = 0x01, // 00000001
    //    Pipeline = 0x02, // 00000010
    //    minimized = 0x04, // 00000100
    //    maximized = 0x08  // 00001000
    //};

    //enum class ResourceType
    //{
    //    Mesh , // 00000001
    //    Pipeline , // 00000010
    //};

    /*enum class ResourceType : unsigned long
    {
        Undefined = 0 << 8,
        SceneGraph = 1 << 8,
        Mesh = 2 << 8,
        Skeleton = 3 << 8,
        Animation = 4 << 8,
        Material = 5 << 8,
        Code = 6 << 8,
        Shader = 7 << 8,
        Texture = 8 << 8,
        ParticleEffect = 9 << 8,
        Pipeline = 10 << 8
    };*/

    using ResourceHandle = unsigned long;

    struct ResourceDescriptor
    {
        ResourceDescriptor() {}
        ResourceDescriptor(ResourceHandle handle, ResourceType type)
        {
            this->handle = handle;
            this->type = type;
        }

        ResourceHandle  handle;
        ResourceType    type;
    };

    class Resource /*: public Object*/
    {
    public:
        Resource();
        //Resource(const Resource& resource, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~Resource();

        //OBJECT_META_FUNCTION(Resource);

        virtual bool load(const std::string& res) = 0;
        virtual void unload() = 0;

        ResourceHandle  getResourceHandle() const { return _descriptor.handle; }
        ResourceType    getResourceType() const { return _descriptor.type; }

        void buildDescriptor(const ResourceDescriptor& des);

    protected:
        ResourceDescriptor      _descriptor;
    };

    class ResourceManager /*: public Object*/
    {
    public:
        ResourceManager(ResourceType type);
//        ResourceManager(const ResourceManager& res_mgr, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        virtual ~ResourceManager();

//        OBJECT_META_FUNCTION(ResourceManager);
        virtual bool create(const std::string& res) = 0;

        //ResourceType getType() const { return _type; }

//        virtual bool create(const std::string& res) = 0;
        
        void add(Resource* resource);
        void remove(ResourceHandle handle);
        bool has(Resource* resource);
        bool has(ResourceHandle handle);

    protected:
        ResourceHandle getNextLocalResHandle();
        ResourceHandle generateGlobalResHandle();
        
        using ResourceMap = std::unordered_map<ResourceHandle, Resource*>;
    protected:
        ResourceMap     _resources;
        ResourceType    _type;
        ResourceHandle  _next_handle;
    };
//
//    class ResourceMap /*: public Object*/
//    {
//    public:
//        ResourceMap();
//        //ResourceMap(const ResourceMap& res_map, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
//        virtual ~ResourceMap();
//
//        //OBJECT_META_FUNCTION(ResourceMap);
//        
//        void registerResource(ResourceType type);
//        void unregisterResource(ResourceType type);
//        bool hasRegistered(ResourceType type);
//
//    protected:
//        std::unordered_map<ResourceType, ResourceManager*>    _res_map;
//    };
}

#endif // COMMON_RESOURCE_H