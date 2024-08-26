#include "logger.h"

#include <sstream>

using namespace std;

void impress::Logger::debug(const std::string &message) {
    log(DEBUG, message);
}

void impress::Logger::info(const std::string &message) {
    log(INFO, message);
}

void impress::Logger::warn(const std::string &message) {
    log(WARN, message);
}

void impress::Logger::error(const std::string &message) {
    log(ERROR, message);
}

void impress::Logger::log(const std::string &level, const std::string &message) {
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
           << local_time.tm_sec
           << level << ": " << message;
    write(stream.str());
}
