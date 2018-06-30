#include "logger.h"

std::string getDateNow(){

    struct timeval myTime;
    struct tm *time_st;
    char ret_str[64];

    gettimeofday(&myTime, NULL);
    time_st = localtime(&myTime.tv_sec);

    sprintf(ret_str, FORMAT_STR_DATE, time_st->tm_year+1900, time_st->tm_mon+1, time_st->tm_mday);

    return std::string(ret_str);
}

std::string getTimeNow(){
    struct timeval myTime;
    struct tm *time_st;
    char ret_str[64];

    gettimeofday(&myTime, NULL);
    time_st = localtime(&myTime.tv_sec);

    sprintf(ret_str, FORMAT_STR_TIME_MSEC, time_st->tm_hour, time_st->tm_min, time_st->tm_sec, myTime.tv_usec);

    return std::string(ret_str);
}

void write_log(const LogLevel::type& logLevel, const char* fileName, const char* funcName, const int lineNum, const char* format, ...){

    // 指定したレベル以下のログは出力しない
    if (logLevel < LOG_LEVEL)
        return;

    char message[512] = { 0 };
    va_list args;

    va_start(args, format);

    vsprintf(message, format, args);

    // ログを出力する処理
    std::ofstream ofs;
    ofs.open(LOG_DIR + getDateNow() + ".log", std::ios::app);

    ofs << getTimeNow() << " "
        << "[" << LogLevel::ToString(logLevel) << "]"
        << "[" << fileName << "]"
        << "[" << funcName << "]"
        << "[" << lineNum << "]"
        << message
        << std::endl;

    ofs.close();

    va_end(args);

}
