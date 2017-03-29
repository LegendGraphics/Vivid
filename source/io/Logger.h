#ifndef IO_LOGGER_H
#define IO_LOGGER_H

#include <ostream>
#include <fstream>

#include "base/Singleton.hpp"
#include "base/String.h"
#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

#define cLog *(te::ConsoleLogger::getInstance())
#define fLog *(te::FileLogger::getInstance())

namespace te
{
    class FileLogger: public Singleton<FileLogger>
    {
    public:
        virtual FileLogger& operator<<(const String& msg);
        virtual FileLogger& operator<<(const Vector3& v);
        virtual FileLogger& operator<<(const Vector4& v);
        virtual FileLogger& operator<<(const Matrix& m);
        virtual FileLogger& operator<<(const Quaternion& q);
    private:
        std::ofstream   _fout;
    };

    class ConsoleLogger: public Singleton<ConsoleLogger>
    {
    public:
        ConsoleLogger();
    public:
        virtual ConsoleLogger& operator<<(const String& msg);
        virtual ConsoleLogger& operator<<(const Vector3& v);
        virtual ConsoleLogger& operator<<(const Vector4& v);
        virtual ConsoleLogger& operator<<(const Matrix& m);
        virtual ConsoleLogger& operator<<(const Quaternion& q);
    private:
        std::ostream   _cout;
    };
}

#endif // IO_LOGGER_H