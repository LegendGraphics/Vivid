#include "common/Component.h"

namespace te
{
    Component::Component()
        :_enabled(true),
        _owner(nullptr),
        _type(MetaType::DATA)
    {

    }

    Component::Component(MetaType type)
        :_enabled(true),
        _owner(nullptr),
        _type(type)
    {}

    Component::Component(const Component& component, const CopyOperator& copyop)
        :_enabled(component._enabled),
        _owner(nullptr),
        _type(MetaType::DATA)
    {
    }

    Component::~Component() {}


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

    Behavior::Behavior()
        :Component(MetaType::BEHAVIOR)
    {}

    Behavior::~Behavior()
    {}

    void Behavior::init()
    {}

    void Behavior::update()
    {}
}







