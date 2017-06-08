#include "io/Logger.h"
#include <iostream>
#include <cstdarg>
#include "base/String.h"

namespace te
{
    FileLogger* Singleton<FileLogger>::_singleton = nullptr;

    FileLogger& FileLogger::operator<<(const String& msg)
    {
        _fout << msg << "\n";
        return *this;
    }
    FileLogger& FileLogger::operator<<(const Vector3& v)
    {
        _fout << StringUtils::format("Vector --- x=%f, y=%f, z=%f\n", v.x, v.y, v.z);
        return *this;
    }
    FileLogger& FileLogger::operator<<(const Vector4& v)
    {
        _fout << StringUtils::format("Vector --- x=%f, y=%f, z=%f, w=%f\n", v.x, v.y, v.z, v.w);
        return *this;
    }
    FileLogger& FileLogger::operator<<(const Matrix& m)
    {
        _fout << StringUtils::format("Matrix ---\n"
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
        _fout << StringUtils::format("Quaternion --- w=%f, x=%f, y=%f, z=%f\n", q.w, q.v.x, q.v.y, q.v.z);
        return *this;
    }


    ConsoleLogger* Singleton<ConsoleLogger>::_singleton = nullptr;

    ConsoleLogger::ConsoleLogger()
        :_cout(std::cout.rdbuf())
    {}

    ConsoleLogger& ConsoleLogger::operator<<(const String& msg)
    {
        _cout << msg << "\n";
        return *this;
    }

    ConsoleLogger& ConsoleLogger::operator<<(const Vector3& v)
    {
        _cout << StringUtils::format("Vector --- x=%f, y=%f, z=%f\n", v.x, v.y, v.z);
        return *this;
    }
    ConsoleLogger& ConsoleLogger::operator<<(const Vector4& v)
    {
        _cout << StringUtils::format("Vector --- x=%f, y=%f, z=%f, w=%f\n", v.x, v.y, v.z, v.w);
        return *this;
    }
    ConsoleLogger& ConsoleLogger::operator<<(const Matrix& m)
    {
        _cout << StringUtils::format("Matrix ---\n"
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
        _cout << StringUtils::format("Quaternion --- w=%f, x=%f, y=%f, z=%f\n", q.w, q.v.x, q.v.y, q.v.z);
        return *this;
    }
}