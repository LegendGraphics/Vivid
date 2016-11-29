#include "UniqueString.h"

using namespace te;

UniqueString::UniqueString(const te::String& theName)
    : m_name(theName)
{
}

UniqueString::~UniqueString()
{
}

UniqueString*
UniqueString::find(const te::String& theName, bool bCreateIfNotFound /* = true */)
{
    UniqueStrings::iterator iter;
    iter = uniqueStrings().find(theName);
    if (iter != uniqueStrings().end())
        return iter->second.get();

    if (!bCreateIfNotFound)
        return NULL;

    UniqueString* pRet = new UniqueString(theName);
    uniqueStrings().insert(std::make_pair<te::String, UniqueStringPtr>(theName, UniqueStringPtr(pRet)));
    return pRet;
}

UniqueString::UniqueStrings&
UniqueString::uniqueStrings()
{
    static UniqueString::UniqueStrings m_uniqueStrings;
    return m_uniqueStrings;
}
