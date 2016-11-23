#include "common/component.h"

Component::Component()
    :_owner(nullptr),
    _enabled(true)
{

}

Component::~Component(){}

bool Component::init()
{
    return true;
}

void Component::setEnabled(bool enabled)
{
    _enabled = enabled;
}

void Component::setName(const std::string& name)
{
    _name = name;
}

void Component::setOwner(Node *owner)
{
    _owner = owner;
}




