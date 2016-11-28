#include "common/object.h"

namespace te
{
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
}