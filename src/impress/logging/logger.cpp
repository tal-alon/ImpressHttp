#include "logger.h"

#include <sstream>

using namespace std;
using namespace impress;


std::string impress::level_to_string(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
    }
}

void impress::Logger::debug(const std::string &message) {
    log(LogLevel::DEBUG, message);
}

void impress::Logger::info(const std::string &message) {
    log(LogLevel::INFO, message);
}

void impress::Logger::warn(const std::string &message) {
    log(LogLevel::WARN, message);
}

void impress::Logger::error(const std::string &message) {
    log(LogLevel::ERROR, message);
}

void impress::Logger::log(LogLevel level, const std::string &message) {
    // only log if the level is greater than or equal to the logger's level
    if (level < m_level) {
        return;
    }
    _log(level, message);
}

void Logger::_log(LogLevel level, const string &message) {
    time_t now = time(nullptr);
    tm local_time{};
    localtime_s(&local_time, &now);
    stringstream stream;
    stream << "["
           // timestamp:
           << local_time.tm_year + 1900 << '-'
           << local_time.tm_mon + 1 << '-'
           << local_time.tm_mday << ' '
           << local_time.tm_hour << ':'
           << local_time.tm_min << ':'
           << local_time.tm_sec << "] "

           // log level:
           << level_to_string(level) << ": "

           // message:
           << message << endl;

    write(stream.str());
}
