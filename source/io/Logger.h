#ifndef IO_LOGGER_H
#define IO_LOGGER_H

#include <ostream>
#include <fstream>
#include <string>

#include "math/Vector3.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"

#define cLog *(te::ConsoleLogger::getInstance())
#define fLog *(te::FileLogger::getInstance())

namespace te
{
    std::string format(const char* format, ...);

    class FileLogger
    {
    public:
        static FileLogger* getInstance();
    public:
        virtual FileLogger& operator<<(const std::string& msg);
        virtual FileLogger& operator<<(const Vector3& v);
        virtual FileLogger& operator<<(const Matrix& m);
        virtual FileLogger& operator<<(const Quaternion& q);
    private:
        FileLogger() = default;
    private:
        static FileLogger* _logger;

        std::ofstream   _fout;
    };

    class ConsoleLogger
    {
    public:
        static ConsoleLogger* getInstance();
    public:
        virtual ConsoleLogger& operator<<(const std::string& msg);
        virtual ConsoleLogger& operator<<(const Vector3& v);
        virtual ConsoleLogger& operator<<(const Matrix& m);
        virtual ConsoleLogger& operator<<(const Quaternion& q);
    private:
        ConsoleLogger();
    private:
        static ConsoleLogger* _logger;

        std::ostream   _cout;
    };

}

#endif // IO_LOGGER_H