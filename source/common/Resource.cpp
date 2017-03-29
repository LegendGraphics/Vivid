#include "common/Resource.h"
#include "common/Mesh.h"

namespace te
{
    Resource::Resource()
    {}

    /*Resource::Resource(const Resource& resource, const CopyOperator& copyop)
    {}*/

    Resource::~Resource(){}

    void Resource::descriptor(const ResourceDescriptor& des)
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
        return ++_next_handle;
    }

    ResourceHandle ResourceManager::generateGlobalResHandle()
    {
        ResourceHandle local_handle = getNextLocalResHandle();
        return ResourceHandle(_type) + local_handle;
    }

    ResourceDescriptor ResourceManager::buildDescriptor(const String& id)
    {
        ResourceHandle global_handle = generateGlobalResHandle();
        return ResourceDescriptor(global_handle, _type, id);
    }

    void ResourceManager::add(Resource* resource)
    {
        if (resource->getResourceType() == _type && !has(resource))
        {
            _resources[resource->getResourceHandle()] = resource;
            _id_maps.insert({ resource->getResourceId(), resource->getResourceHandle() });
        }
    }

    void ResourceManager::remove(ResourceHandle handle)
    {
        if (has(handle))
        {
            _id_maps.erase(_resources[handle]->getResourceId());
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

    bool ResourceManager::exist(const String& id)
    {
        auto search = _id_maps.find(id);
        if (search != _id_maps.end()) return true;
        else return false;
    }


    ResourceMapper* Singleton<ResourceMapper>::_singleton = nullptr;

    ResourceMapper::ResourceMapper()
    {
        initialize();
    }

    ResourceMapper::~ResourceMapper()
    {

    }

    /*ResourceMap::ResourceMap(const ResourceMap& res_map, const CopyOperator& copyop)
    {}*/

    /*ResourceMapper::~ResourceMapper()
    {}*/

    // initialize all resource managers
    void ResourceMapper::initialize()
    {
        add<MeshManager>();
    }

    void ResourceMapper::clear()
    {
        remove<MeshManager>();
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
        delete _mgr_map[manager_id];
        _mgr_map[manager_id] = nullptr;
        _mgr_types[manager_id] = false;
    }
    bool ResourceMapper::hasResManager(int manager_id)
    {
        return _mgr_types[manager_id];
    }
}