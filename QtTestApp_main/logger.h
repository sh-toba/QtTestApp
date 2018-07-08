#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <sys/time.h>
#include <QThread>

#define FORMAT_STR_DATE "%d-%02d-%02d"
#define FORMAT_STR_TIME "%02d:02d:02d"
#define FORMAT_STR_TIME_MSEC "%02d:%02d:%02d.%06d"
#define LOG_DIR std::string("/var/log/test/")
#define LOG_LEVEL LogLevel::Info

class LogLevel
{
public:
    enum type
    {
        Info= 1,
        Debug,
        Warn,
        Error,
    };
    static std::string ToString(LogLevel::type LogLevel)
    {
        switch(LogLevel)
        {
        case LogLevel::Info: return "Info";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Warn: return "WARN";
        case LogLevel::Error: return "ERROR";
        default: return "UNKNOWN";
        }
    }
};

std::string getDateNow();
std::string getTimeNow();
void write_log(const LogLevel::type& logLevel, const char* fileName, const char* funcName, const int lineNum, const char* format, ...);

#define LOG_INFO(format, ...)   write_log(LogLevel::Info,  __FILE__, __FUNCTION__, __LINE__, format, __VA_ARGS__);
#define LOG_DEBUG(format, ...)  write_log(LogLevel::Debug, __FILE__, __FUNCTION__, __LINE__, format, __VA_ARGS__);
#define LOG_WARN(format, ...)   write_log(LogLevel::Warn,  __FILE__, __FUNCTION__, __LINE__, format, __VA_ARGS__);
#define LOG_ERROR(format, ...)  write_log(LogLevel::Error, __FILE__, __FUNCTION__, __LINE__, format, __VA_ARGS__);

#endif // LOGGER_H
