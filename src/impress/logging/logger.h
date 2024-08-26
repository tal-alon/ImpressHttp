#ifndef IMPRESSHTTP_LOGGER_H
#define IMPRESSHTTP_LOGGER_H

#include <string>


namespace impress {
    enum class LogLevel {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    // LogLevel convenience operators
    constexpr bool operator<(LogLevel lhs, LogLevel rhs);
    constexpr bool operator<=(LogLevel lhs, LogLevel rhs);
    constexpr bool operator>(LogLevel lhs, LogLevel rhs);
    constexpr bool operator>=(LogLevel lhs, LogLevel rhs);
    std::string level_to_string(LogLevel level);

    class Logger {
        LogLevel m_level = LogLevel::INFO;

    public:
        virtual ~Logger() = default;
        void debug(const std::string &message);
        void info(const std::string &message);
        void warn(const std::string &message);
        void error(const std::string &message);

    protected:
        virtual void write(const std::string &message) = 0;

    private:
        void log(LogLevel level, const std::string &message);
        void _log(LogLevel level, const std::string &message);
    };

}// namespace impress

#endif//IMPRESSHTTP_LOGGER_H
