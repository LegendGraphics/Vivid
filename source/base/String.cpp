#include "base/String.h"

namespace te
{
    String StringUtils::format(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
#ifndef _MSC_VER
        size_t size = std::snprintf(nullptr, 0, format, args) + 1; // Extra space for '\0'
        std::unique_ptr<char[]> buf(new char[size]);
        std::vsnprintf(buf.get(), size, format, args);
        return String(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
#else
        int size = _vscprintf(format, args);
        String result(++size, 0);
        vsnprintf_s((char*)result.data(), size, _TRUNCATE, format, args);
        return result;
#endif
        va_end(args);
    }

    char* StringUtils::convertToChar(const String& str)
    {
        size_t len = str.length();
        char* cstr = new char[len+1];
        str.copy(cstr, len);
        cstr[len] = '\0';
        return cstr;
    }

    String StringUtils::convertToString(const char* cstr)
    {
        return String(cstr);
    }

}


