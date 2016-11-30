#include "common/component.h"

 using namespace te;

Component::Component()
    :_enabled(true)
{

}

Component::~Component(){}

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

void Component::setName(const std::string& name)
{
    _name = name;
}





