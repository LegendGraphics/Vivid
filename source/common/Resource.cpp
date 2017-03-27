#include "common/Resource.h"
#include "common/Mesh.h"

namespace te
{
    Resource::Resource()
    {}

    /*Resource::Resource(const Resource& resource, const CopyOperator& copyop)
    {}*/

    Resource::~Resource(){}

    void Resource::buildDescriptor(const ResourceDescriptor& des)
    {
        _descriptor = des;
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

    ResourceHandle ResourceManager::getNextLocalResHandle()
    {
        return _next_handle++;
    }

    ResourceHandle ResourceManager::generateGlobalResHandle()
    {
        return ResourceHandle(_type) + _next_handle;
    }

    void ResourceManager::add(Resource* resource)
    {
        if (resource->getResourceType() == _type && !has(resource))
        {
            ResourceHandle global_handle = generateGlobalResHandle();
            resource->buildDescriptor(ResourceDescriptor(global_handle, _type));
            _resources.insert({ global_handle, resource });
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

    ResourceMapper::ResourceMapper()
    {}

    /*ResourceMap::ResourceMap(const ResourceMap& res_map, const CopyOperator& copyop)
    {}*/

    ResourceMapper::~ResourceMapper()
    {}

    // initialize all resource managers
    void ResourceMapper::initialize()
    {
        add<MeshManager>();
    }

    ResourceManager* ResourceMapper::getResManager(int manager_id)
    {
        return _mgr_map[manager_id];
    }

    ResourceManager* ResourceMapper::addResManager(ResourceManager* mgr, int manager_id)
    {
        _mgr_map[manager_id] = mgr;
        _mgr_types[manager_id] = true;
        return mgr;
    }
    void ResourceMapper::removeResManager(int manager_id)
    {
        _mgr_map[manager_id] = nullptr;
        _mgr_types[manager_id] = false;
    }
    bool ResourceMapper::hasResManager(int manager_id)
    {
        return _mgr_types[manager_id];
    }
}