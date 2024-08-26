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
    std::string level_to_string(LogLevel level);

    class Logger {
    public:
        virtual void debug(const std::string &message);
        virtual void info(const std::string &message);
        virtual void warn(const std::string &message);
        virtual void error(const std::string &message);

    protected:

        virtual void log(LogLevel level, const std::string &message);
        virtual void write(const std::string &message) = 0;
    };

}// namespace impress

#endif//IMPRESSHTTP_LOGGER_H
