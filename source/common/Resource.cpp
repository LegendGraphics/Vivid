#include "common/Resource.h"

namespace te
{
    ResourceHandle Resource::HANDLE_COUNT = 0;

    Resource::Resource(ResourceType type)
        :_type(type),
        _handle(0),
        _loaded(false)
    {}

    Resource::Resource(const Resource& resource, const CopyOperator& copyop)
    {}

    Resource::~Resource(){}

    void Resource::release()
    {}

    bool Resource::load(const std::string& res)
    {
        // Resources can only be loaded once
        if (_loaded) return false;

        // if res does not exists, return false;

        _loaded = true;

        return true;
    }

    void Resource::unload()
    {
        release();
        _loaded = false;
    }

    void Resource::setResourceHandle()
    {
        if (_loaded) _handle = HANDLE_COUNT++;
    }

    ResourceManager::ResourceManager(ResourceType type)
        :_type(type)
    {

    }

    ResourceManager::ResourceManager(const ResourceManager& res_mgr, const CopyOperator& copyop)
    {}

    ResourceManager::~ResourceManager()
    {}

    void ResourceManager::addResource(Resource* resource)
    {
        if (resource->getType() == _type && !hasResource(resource))
        {
            _resources.insert({ resource->getResourceHandle(), resource });
        }
    }

    void ResourceManager::removeResource(ResourceHandle handle)
    {
        if (hasResource(handle))
        {
            _resources.erase(handle);
        }
    }

    bool ResourceManager::hasResource(Resource* resource)
    {
        ResourceHandle handle = resource->getResourceHandle();
        return hasResource(handle);
    }

    bool ResourceManager::hasResource(ResourceHandle handle)
    {
        if (_resources.find(handle) != _resources.end()) return true;
        else return false;
    }

    ResourceMap::ResourceMap()
    {}

    ResourceMap::ResourceMap(const ResourceMap& res_map, const CopyOperator& copyop)
    {}

    ResourceMap::~ResourceMap()
    {}

    void ResourceMap::registerResource(ResourceType type)
    {
        if (!hasRegistered(type))
            _res_map.insert({type, new ResourceManager(type)});
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