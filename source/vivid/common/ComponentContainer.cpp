#include "vivid/common/ComponentContainer.h"
#include "vivid/common/Component.h"
#include "vivid/base/Assert.h"

namespace vivid
{
    ComponentContainer::ComponentContainer()
        :_owner(nullptr)
    {
        reset();
    }

    ComponentContainer::ComponentContainer(Node* owner)
        : _owner(owner)
    {
        reset();
    }

    ComponentContainer::ComponentContainer(const ComponentContainer& ccontainer, const CopyOperator& copyop)
    {
        copyop(&ccontainer);
    }


    ComponentContainer::~ComponentContainer()
    {
        destroyAll();
    }

    Component* ComponentContainer::get(int component_id)
    {
        mASSERT(component_id < MAX_AMOUNT_OF_COMPONENTS, "Component id exceeds the max amount of components!");
        mASSERT(_component_types[component_id] == true, "No such component exists!");
        return _component_map[component_id];
    }

    void ComponentContainer::add(Component *component, int component_id)
    {
        mASSERT(component_id < MAX_AMOUNT_OF_COMPONENTS, "Component id exceeds the max amount of components!");
        mASSERT(_component_types[component_id] == false, "Component already exists!");

        _component_map[component_id] = component;
        _component_types[component_id] = true;
    }

    void ComponentContainer::remove(int component_id)
    {
        mASSERT(component_id < MAX_AMOUNT_OF_COMPONENTS, "Component id exceeds the max amount of components!");
        mASSERT(_component_types[component_id] == true, "No such component exists!");

        _component_map[component_id] = nullptr;
        _component_types[component_id] = false;
    }

    void ComponentContainer::reset()
    {
        _component_map.fill(nullptr);
        _component_types.reset();
    }

    void ComponentContainer::destroyAll()
    {
        for (auto& component : _component_map)
        {
            delete component;
        }
    }

    bool ComponentContainer::has(int component_id)
    {
        mASSERT(component_id < MAX_AMOUNT_OF_COMPONENTS, "Component id exceeds the max amount of components!");

        return _component_types[component_id];
    }

    void ComponentContainer::updateBehavior()
    {
        if (!_component_map.empty())
        {
            ComponentMap::iterator iter = _component_map.begin();
            while (iter != _component_map.end())
            {
                Component* component = *iter;
                if (component && component->getType() == ComponentType::LOGIC_BEHAVVIVID_IOR)
                {
                    Behavior* behavior = dynamic_cast<Behavior*>(component);
                    behavior->update();
                }
                iter++;
            }
        }
    }

    void ComponentContainer::updateRender()
    {
        if (!_component_map.empty())
        {
            ComponentMap::iterator iter = _component_map.begin();
            while (iter != _component_map.end())
            {
                Component* component = *iter;
                if (component && component->getType() == ComponentType::UPLOAD_TO_RENDER)
                {
                    Render* render = dynamic_cast<Render*>(component);
                    render->update();
                }
                iter++;
            }
        }
    }
}



