#include "vivid/common/Resource.h"
#include "vivid/common/Mesh.h"
#include "vivid/common/Node.h"
#include "vivid/common/Pipeline.h"
#include "vivid/common/Shader.h"
#include "vivid/common/Material.h"

namespace vivid
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
        :_type(type)
    {

    }

   /* ResourceManager::ResourceManager(const ResourceManager& res_mgr, const CopyOperator& copyop)
    {}*/

    ResourceManager::~ResourceManager()
    {}

    ResourceHandle ResourceManager::getNextLocalResHandle()
    {
        if (!_free_list.empty())
        {
            ResourceHandle handle = _free_list.back();
            _free_list.pop_back();
            return handle;
        }
        else
        {
            _resources.push_back(ResourcePtr(nullptr));
            return _resources.size(); // handle starts from 1
        }
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
            _resources[resource->getResourceHandle() - ResourceHandle(_type) - 1] = ResourcePtr(resource);
            _id_maps.insert({ resource->getResourceId(), resource->getResourceHandle() });
        }
    }

    void ResourceManager::remove(ResourceHandle global_handle)
    {
        if (has(global_handle))
        {
            ResourceHandle local_handle = global_handle - ResourceHandle(_type);
            _id_maps.erase(_resources[local_handle - 1]->getResourceId());
            _resources[local_handle - 1] = ResourcePtr(nullptr);
            _free_list.push_back(local_handle); // freelist holds local handle
        }
    }

    bool ResourceManager::has(Resource* resource)
    {
        return has(resource->getResourceHandle());
    }

    bool ResourceManager::has(ResourceHandle global_handle)
    {
        ResourceHandle local_handle = global_handle - ResourceHandle(_type);
        if (local_handle > 0 && local_handle <= _resources.size() && _resources[local_handle - 1]) return true;
        else return false;
    }

    bool ResourceManager::exist(const String& id)
    {
        auto search = _id_maps.find(id);
        if (search != _id_maps.end()) return true;
        else return false;
    }

    ResourceHandle ResourceManager::getResourceHandle(const String& id)
    {
        if (exist(id)) return _id_maps[id];
        else return 0;
    }

    ResourcePtr ResourceManager::getResourcePtr(ResourceHandle global_handle)
    {
        ResourceHandle local_handle = global_handle - ResourceHandle(_type);
        if (local_handle > 0 && local_handle <= _resources.size() && _resources[local_handle - 1])
            return _resources[local_handle - 1];
        else return ResourcePtr(nullptr);
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
        add<MetaNodeManager>();
        add<PipelineManager>();
        add<ShaderManager>();
        add<MaterialManager>();
        add<TextureManager>();
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