#pragma once
#include <string>


namespace impress {
    enum class LogLevel {
        DEBUG=0,
        INFO=10,
        WARN=20,
        ERROR=30
    };

    std::string level_to_string(LogLevel level);

    class Logger {
    public:
        virtual ~Logger() = default;
        void debug(const std::string &message);
        void info(const std::string &message);
        void warn(const std::string &message);
        void error(const std::string &message);

    protected:
        LogLevel m_level = LogLevel::INFO;
        virtual void write(const std::string &message) = 0;

    private:
        void log(LogLevel level, const std::string &message);
        void _log(LogLevel level, const std::string &message);
    };

}// namespace impress
