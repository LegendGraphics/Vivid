#ifndef VIVID_COMMON_COMPONENT_CONTAINER_H
#define VIVID_COMMON_COMPONENT_CONTAINER_H

#include <array>
#include <bitset>

#include "vivid/common/Clone.h"

namespace vivid
{
    const int MAX_AMOUNT_OF_COMPONENTS = 12;
}

namespace vivid
{
    class Component;
    class Node;

    class ComponentContainer : public Cloneable
    {    
    private:
        typedef std::array<Component*, MAX_AMOUNT_OF_COMPONENTS> ComponentMap;
        typedef std::bitset<MAX_AMOUNT_OF_COMPONENTS> ComponentTypeList;

    public:
        ComponentContainer();
        ComponentContainer(Node* owner);
        ComponentContainer(const ComponentContainer& ccontainer, const CopyOperator& copyop = CopyOperator::SHALLOW_COPY);
        ~ComponentContainer();

        void add(Component* component, int component_id);
        void remove(int component_id);
        void reset();
        Component* get(int component_id);
        bool has(int component_id);

        bool isEmpty() const { return _component_map.empty(); } 

        void updateBehavior();
        void updateRender();

    private:
        void destroyAll();

    private:
        ComponentMap _component_map;
        ComponentTypeList _component_types;
        Node *_owner;
    };

}



#endif // VIVID_COMMON_COMPONENT_CONTAINER_H
