#ifndef COMMON_COMPONENT_H
#define COMMON_COMPONENT_H

#include <string>

#include "base/ref.h"

class Node;

class Component: public Ref
{
protected:
    Component();
    virtual ~Component();
public:
    virtual bool init();

    bool isEnabled() const { return _enabled; }
    void setEnabled(bool enabled);

    const std::string& getName() const { return _name; }
    void setName(const std::string& name);

    Node* getOwner() const { return _owner; }
    void setOwner(Node *owner);

    virtual void update(float delta);

protected:
    Node* _owner;
    std::string _name;
    bool _enabled;
};

#endif // COMMON_COMPONENT_H