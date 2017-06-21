#ifndef VIVID_BASE_STRING_H
#define VIVID_BASE_STRING_H

#include <string>
#include <cstdarg>

namespace vivid
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

#endif // VIVID_BASE_STRING_H
