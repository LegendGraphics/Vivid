#include "common/Resource.h"

namespace te
{
    Resource::Resource()
    {}

    /*Resource::Resource(const Resource& resource, const CopyOperator& copyop)
    {}*/

    Resource::~Resource(){}

    bool Resource::load(const std::string& res)
    {
        return false;
    }

    void Resource::unload()
    {
    }

    ResourceManager::ResourceManager(ResourceType type)
        :_type(type),
        _next_handle(0)
    {

    }

   /* ResourceManager::ResourceManager(const ResourceManager& res_mgr, const CopyOperator& copyop)
    {}*/

    ResourceManager::~ResourceManager()
    {}

    ResourceHandle ResourceManager::getNextResHandle()
    {
        return _next_handle++;
    }

    void ResourceManager::add(Resource* resource)
    {
        if (resource->getType() == _type && !has(resource))
        {
            _resources.insert({ resource->getResourceHandle(), resource });
        }
    }

    void ResourceManager::remove(ResourceHandle handle)
    {
        if (has(handle))
        {
            _resources.erase(handle);
        }
    }

    bool ResourceManager::has(Resource* resource)
    {
        ResourceHandle handle = resource->getResourceHandle();
        return has(handle);
    }

    bool ResourceManager::has(ResourceHandle handle)
    {
        if (_resources.find(handle) != _resources.end()) return true;
        else return false;
    }

    ResourceMap::ResourceMap()
    {}

    /*ResourceMap::ResourceMap(const ResourceMap& res_map, const CopyOperator& copyop)
    {}*/

    ResourceMap::~ResourceMap()
    {}

    void ResourceMap::registerResource(ResourceType type)
    {
        /*if (!hasRegistered(type))
            _res_map.insert({type, new ResourceManager(type)});*/
    }

    void ResourceMap::unregisterResource(ResourceType type)
    {
        if (hasRegistered(type))
            _res_map.erase(type);
    }

    bool ResourceMap::hasRegistered(ResourceType type)
    {
        if (_res_map.find(type) == _res_map.end())
            return false;
        else return true;
    }
}