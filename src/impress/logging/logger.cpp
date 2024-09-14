#include "logger.h"

#include <sstream>

using namespace std;


std::string level_to_string(LogLevel level) {
    switch (level) {
        case DEBUG_LVL:
            return "DEBUG";
        case INFO_LVL:
            return "INFO ";
        case WARN_LVL:
            return "WARN ";
        case ERROR_LVL:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

void Logger::debug(const std::string &message) {
    log(DEBUG_LVL, message);
}

void Logger::info(const std::string &message) {
    log(INFO_LVL, message);
}

void Logger::warn(const std::string &message) {
    log(WARN_LVL, message);
}

void Logger::error(const std::string &message) {
    log(ERROR_LVL, message);
}

void Logger::log(LogLevel level, const std::string &message) {
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
           << message;

    write(stream.str());
}
