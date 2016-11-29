#include "common/copy_operator.h"
#include "common/object.h"
#include "common/node.h"


using namespace te;

#define COPY_FUNCTOR( TYPE ) \
    TYPE* CopyOperator::operator() (const TYPE* obj) const \
    { \
    if (obj && (_flag == DEEP_COPY)) \
    return te::clone(obj, *this); \
    else \
    return const_cast<TYPE*>(obj); \
}

COPY_FUNCTOR(Object)
COPY_FUNCTOR(Node)
