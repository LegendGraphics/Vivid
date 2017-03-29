#include "common/Component.h"

namespace te
{
    Component::Component()
        :_enabled(true),
        _owner(nullptr)
    {

    }

    Component::Component(const Component& component, const CopyOperator& copyop)
        :_enabled(component._enabled),
        _owner(nullptr)
    {
    }

    Component::~Component() {}

    void Component::init()
    {
    }

    void Component::update()
    {

    }

    void Component::setEnabled(bool enabled)
    {
        _enabled = enabled;
    }

    void Component::setName(const String& name)
    {
        _name = name;
    }

    void Component::setOwner(Node* owner)
    {
        _owner = owner;
    }
}







