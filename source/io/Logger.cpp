#include "io/Logger.h"

#include <cstdarg>

namespace te
{
    std::string format(const char* format, ...)
    {
        va_list args;
        va_start(args, format);
#ifndef _MSC_VER
        size_t size = std::snprintf(nullptr, 0, format, args) + 1; // Extra space for '\0'
        std::unique_ptr<char[]> buf(new char[size]);
        std::vsnprintf(buf.get(), size, format, args);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
#else
        int size = _vscprintf(format, args);
        std::string result(++size, 0);
        vsnprintf_s((char*)result.data(), size, _TRUNCATE, format, args);
        return result;
#endif
        va_end(args);
    }

    FileLogger* FileLogger::_logger = nullptr;

    FileLogger* FileLogger::getInstance()
    {
        if (!_logger)
        {
            _logger = new FileLogger();
        }

        return _logger;
    }

    FileLogger& FileLogger::operator<<(const std::string& msg)
    {
        _fout << msg << "\n";
        return *this;
    }
    FileLogger& FileLogger::operator<<(const Vector3& v)
    {
        _fout << format("Vector --- x=%f, y=%f, z=%f\n", v.x, v.y, v.z);
        return *this;
    }
    FileLogger& FileLogger::operator<<(const Matrix& m)
    {
        _fout << format("Matrix ---\n"
                        "%f, %f, %f, %f\n"
                        "%f, %f, %f, %f\n"
                        "%f, %f, %f, %f\n"
                        "%f, %f, %f, %f\n",
                        m(0, 0), m(0, 1), m(0, 2), m(0, 3),
                        m(1, 0), m(1, 1), m(1, 2), m(1, 3), 
                        m(2, 0), m(2, 1), m(2, 2), m(2, 3), 
                        m(3, 0), m(3, 1), m(3, 2), m(3, 3));
        return *this;
    }

    FileLogger& FileLogger::operator<<(const Quaternion& q)
    {
        _fout << format("Quaternion --- w=%f, x=%f, y=%f, z=%f\n", q.w, q.v.x, q.v.y, q.v.z);
        return *this;
    }


    ConsoleLogger* ConsoleLogger::_logger = nullptr;

    ConsoleLogger* ConsoleLogger::getInstance()
    {
        if (!_logger)
        {
            _logger = new ConsoleLogger();
        }

        return _logger;
    }

    ConsoleLogger::ConsoleLogger()
        :_cout(std::cout.rdbuf())
    {}

    ConsoleLogger& ConsoleLogger::operator<<(const std::string& msg)
    {
        _cout << msg << "\n";
        return *this;
    }

    ConsoleLogger& ConsoleLogger::operator<<(const Vector3& v)
    {
        _cout << format("Vector --- x=%f, y=%f, z=%f\n", v.x, v.y, v.z);
        return *this;
    }
    ConsoleLogger& ConsoleLogger::operator<<(const Matrix& m)
    {
        _cout << format("Matrix ---\n"
                        "%f, %f, %f, %f\n"
                        "%f, %f, %f, %f\n"
                        "%f, %f, %f, %f\n"
                        "%f, %f, %f, %f\n",
                        m(0, 0), m(0, 1), m(0, 2), m(0, 3),
                        m(1, 0), m(1, 1), m(1, 2), m(1, 3),
                        m(2, 0), m(2, 1), m(2, 2), m(2, 3),
                        m(3, 0), m(3, 1), m(3, 2), m(3, 3));
        return *this;
    }

    ConsoleLogger& ConsoleLogger::operator<<(const Quaternion& q)
    {
        _cout << format("Quaternion --- w=%f, x=%f, y=%f, z=%f\n", q.w, q.v.x, q.v.y, q.v.z);
        return *this;
    }
}