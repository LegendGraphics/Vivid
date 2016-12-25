#include "common/ComponentContainer.h"
#include "common/Component.h"
#include "base/Assert.h"

using namespace te;

ComponentContainer::ComponentContainer(Node* owner)
    : _owner(owner)
{
}

ComponentContainer::ComponentContainer(const ComponentContainer& ccontainer, const CopyOperator& copyop)
	:_owner(ccontainer._owner)
{
}


ComponentContainer::~ComponentContainer()
{  
}

Component* ComponentContainer::get(int component_id)
{
    TE_ASSERT(component_id < te::MAX_AMOUNT_OF_COMPONENTS, "Component id exceeds the max amount of components!");
    TE_ASSERT(_component_types[component_id] == true, "No such component exists!");
    return _component_map[component_id].get();
}

void ComponentContainer::add(Component *component, int component_id)
{
    TE_ASSERT(component_id < te::MAX_AMOUNT_OF_COMPONENTS, "Component id exceeds the max amount of components!");
    TE_ASSERT(_component_types[component_id] == false, "Component already exists!");
    
    _component_map[component_id] = component;
    _component_types[component_id] = true;
}

void ComponentContainer::remove(int component_id)
{
    TE_ASSERT(component_id < te::MAX_AMOUNT_OF_COMPONENTS, "Component id exceeds the max amount of components!");
    TE_ASSERT(_component_types[component_id] == true, "No such component exists!");

    _component_map[component_id] = nullptr;
    _component_types[component_id] = false;
}

void ComponentContainer::removeAll()
{
    _component_map.fill(nullptr);
    _component_types.reset();
}

bool ComponentContainer::has(int component_id)
{
    TE_ASSERT(component_id < te::MAX_AMOUNT_OF_COMPONENTS, "Component id exceeds the max amount of components!");
    
    return _component_types[component_id];
}

void ComponentContainer::update()
{
    if (!_component_map.empty())
    {
        for (auto& iter : _component_map)
        {
            iter->update();
        }
    }
}

