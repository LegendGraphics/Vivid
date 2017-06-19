#ifndef BASE_STRING_H
#define BASE_STRING_H

#include <string>
#include <cstdarg>

namespace te
{
    typedef std::string String;
    // Utility class for manipulating String
    class StringUtils
    {
    public:
        static String format(const char* format, ...);
        static char* convertToChar(const String& str);
        static String convertToString(const char* cstr);
    };

}

#endif // BASE_STRING_H