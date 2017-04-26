#include "common/Component.h"

namespace te
{
    Component::Component()
        :_enabled(true),
        _owner(nullptr),
        _meta_type(MetaType::DATA),
        _type(ComponentType::UNDEFINED)
    {

    }

    Component::Component(ComponentType type)
        :_enabled(true),
        _owner(nullptr),
        _meta_type(MetaType::DATA),
        _type(type)
    {}

    Component::Component(const Component& component, const CopyOperator& copyop)
    {
        copyop(&component);
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
    {
        _meta_type = Component::MetaType::BEHAVIOR;
        _type = ComponentType::LOGIC_BEHAVIOR;
    }

    Behavior::~Behavior()
    {}

    void Behavior::init()
    {}

    void Behavior::update()
    {}
}







