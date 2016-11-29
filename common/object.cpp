#include "common/object.h"

#include "InterfaceSourceMacros.h"

using namespace te

Object::Object()
{

}

Object::Object(const Object& obj, const CopyOperator& copyop)
    :_name(obj._name)
{
}

Object::~Object()
{
}

TE_IMPLEMENT_INTERFACE(te::Object)
TE_INPLEMENT_START_QUERYINTERFACE(Object)
TE_IMPLEMENT_BASE_QUERYINTERFACE(Ref)
TE_IMPLEMENT_END_QUERYINTERFACE()