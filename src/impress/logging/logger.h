#pragma once
#include <string>

typedef int LogLevel;

constexpr LogLevel DEBUG_LVL = 0;
constexpr LogLevel INFO_LVL = 10;
constexpr LogLevel WARN_LVL = 20;
constexpr LogLevel ERROR_LVL = 30;


std::string level_to_string(LogLevel level);

class Logger {
public:
    virtual ~Logger() = default;
    void debug(const std::string &message);
    void info(const std::string &message);
    void warn(const std::string &message);
    void error(const std::string &message);

protected:
    LogLevel m_level = INFO_LVL;
    virtual void write(const std::string &message) = 0;

private:
    void log(LogLevel level, const std::string &message);
    void _log(LogLevel level, const std::string &message);
};
