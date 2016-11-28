#include "common/copy_operator.h"

namespace te
{
#define COPY_OP( TYPE, FLAG ) \
    TYPE* CopyOperator::operator() (const TYPE* obj) const \
    { \
    if (obj && _flags&FLAG) \
    return osg::clone(obj, *this); \
    else \
    return const_cast<TYPE*>(obj); \
}

    COPY_OP(Object, DEEP_COPY_OBJECTS)
    COPY_OP(Node, DEEP_COPY_NODES)
}