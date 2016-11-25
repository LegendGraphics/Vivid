#ifndef COMMON_COMPONENT_CONTAINER_H
#define COMMON_COMPONENT_CONTAINER_H

#include <string>
#include <unordered_map>

#include "base/ref.h"
#include "base/refptr.hpp"

class Component;
class Node;

class ComponentContainer: public Ref
{    
public:
    ComponentContainer(Node* owner);
    ~ComponentContainer();

    Component* get(const std::string& name);

    bool add(Component* component);
    bool remove(const std::string& name);
    bool remove(Component* component);
    void removeAll();
    void visit(float delta);


    bool isEmpty() const { return _component_map.empty(); } 
private:
    std::unordered_map<std::string, RefPtr<Component>> _component_map;
    Node *_owner;

    friend class Node;


};

#endif // COMMON_COMPONENT_CONTAINER_H