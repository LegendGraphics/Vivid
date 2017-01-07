#include "common/Resource.h"

namespace te
{
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

    bool Resource::load(const char *data, int size)
    {
        // Resources can only be loaded once
        if (_loaded) return false;

        // A NULL pointer can be used if the file could not be loaded
        if (data == nullptr || size <= 0)
        {
           // file not found
            return false;
        }

        _loaded = true;

        return true;
    }

    void Resource::unload()
    {
        release();
        _loaded = false;
    }

    void Resource::setResourceHandle(ResourceHandle handle)
    {
        _handle = handle;
    }

    ResoureManager::ResoureManager(ResourceType type)
        :_type(type)
    {

    }

    ResoureManager::ResoureManager(const ResoureManager& res_mgr, const CopyOperator& copyop)
    {}

    ResoureManager::~ResoureManager()
    {}

    void ResoureManager::addResource(Resource* resource)
    {
        if (resource->getType() == _type && !hasResource(resource))
        {
            _resources.push_back(resource);
            resource->setResourceHandle(_resources.size());
        }
    }

    void ResoureManager::removeResource(ResourceHandle handle)
    {
        if (hasResource(handle))
        {
            int index = handle - 1;
            _resources[index] = nullptr;
        }
    }

    bool ResoureManager::hasResource(Resource* resource)
    {
        ResourceHandle handle = resource->getResourceHandle();
        return hasResource(handle);
    }

    bool ResoureManager::hasResource(ResourceHandle handle)
    {
        ResourceHandle max_handle = _resources.size();
        if (handle <= max_handle) return true;
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
            _res_map.insert({type, new ResoureManager(type)});
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