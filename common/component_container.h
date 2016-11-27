#ifndef COMMON_COMPONENT_CONTAINER_H
#define COMMON_COMPONENT_CONTAINER_H

#include <array>
#include <bitset>

#include "base/ref.h"
#include "base/refptr.hpp"

class Component;
class Node;

class ComponentContainer: public Ref
{    
private:
    typedef std::array<RefPtr<Component>, te::MAX_AMOUNT_OF_COMPONENTS> ComponentMap;
    typedef std::bitset<te::MAX_AMOUNT_OF_COMPONENTS> ComponentTypeList;

public:
    ComponentContainer(Node* owner);
    ~ComponentContainer();

    void add(Component* component, int component_id);
    void remove(int component_id);
    void removeAll();
    Component* get(int component_id);
    bool has(int component_id);

    bool isEmpty() const { return _component_map.empty(); } 

    virtual void update();

private:
    ComponentMap _component_map;
    ComponentTypeList _component_types;
    Node *_owner;
};

namespace te
{
    const int MAX_AMOUNT_OF_COMPONENTS = 32;
}

#endif // COMMON_COMPONENT_CONTAINER_H