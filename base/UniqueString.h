#pragma once

#include "Globals.h"

namespace te
{
    class UniqueString
    {
    private:
        UniqueString(const UniqueString& src);
        UniqueString& operator=(const UniqueString& rhs);

    protected:
        UniqueString(const te::String& theName);

    public:
        virtual ~UniqueString();

        static UniqueString* find(const te::String& theName, bool bCreateIfNotFound = true);

    private:
        typedef std::shared_ptr<UniqueString> UniqueStringPtr;
        typedef std::unordered_map<te::String, UniqueStringPtr> UniqueStrings;

        static UniqueString& uniqueStrings();
        te::String m_name;
    };
}