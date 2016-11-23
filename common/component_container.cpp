#include "common/component_container.h"
#include "base/macros.h"
#include "common/component.h"

ComponentContainer::ComponentContainer(Node* owner)
    : _owner(owner)
{
}

ComponentContainer::~ComponentContainer()
{  
}

Component* ComponentContainer::get(const std::string& name) const
{
    Component* ret = nullptr;

    auto& it = _component_map.find(name);
    if (it != _component_map.end())
    {
        ret = it->second;
    }

    return ret;
}

bool ComponentContainer::add(Component *component)
{
    bool ret = false;
    TE_ASSERT(component != nullptr, "Component must be non-nil");
    TE_ASSERT(component->getOwner() == nullptr, "Component already added. It can't be added again");
    
    auto& component_name = component->getName();

    if (_component_map.find(component_name) != _component_map.end())
    {
        TE_ASSERT(false, "ComponentContainer already have this kind of component");
        return false;
    }
    _component_map[component_name] = component;
    component->setOwner(_owner);
    ret = true;

    return ret;
}

bool ComponentContainer::remove(const std::string& component_name)
{
    bool ret = false;
        
    auto iter = _component_map.find(component_name);
    TE_ASSERT(iter == _component_map.end(), "No such component exists!");

    auto& component = iter->second;
    _component_map.erase(component_name);

    component->setOwner(nullptr);
    ret = true;

    return ret;
}

bool ComponentContainer::remove(Component *com)
{
    return remove(com->getName());
}

void ComponentContainer::removeAll()
{
    if (!_component_map.empty())
    {
        for (auto& iter : _component_map)
        {
            iter.second->setOwner(nullptr);
        }

        _component_map.clear();
    }
}

void ComponentContainer::visit(float delta)
{
    if (!_component_map.empty())
    {
        for (auto& iter : _component_map)
        {
            iter.second->update(delta);
        }
    }
}

