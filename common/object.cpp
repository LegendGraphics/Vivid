#include "common/object.h"

using namespace te;

Object::Object()
{

}

Object::Object(const Object& obj,const CopyOperator& copyop)
    :_name(obj._name)
{
}

Object::~Object()
{
}