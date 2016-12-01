#include "common/object.h"

#include "InterfaceSourceMacros.h"

using namespace te;


TE_IMPLEMENT_INTERFACE(te::Object)
TE_INPLEMENT_START_QUERYINTERFACE(Object)
TE_IMPLEMENT_BASE_QUERYINTERFACE(Ref)
TE_IMPLEMENT_END_QUERYINTERFACE()