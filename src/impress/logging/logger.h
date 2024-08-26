#ifndef IMPRESSHTTP_LOGGER_H
#define IMPRESSHTTP_LOGGER_H

#include <string>

const std::string DEBUG = "DEBUG";
const std::string INFO = "INFO";
const std::string WARN = "WARN";
const std::string ERROR = "ERROR";


namespace impress {

    class Logger {
    public:
        virtual void debug(const std::string &message);
        virtual void info(const std::string &message);
        virtual void warn(const std::string &message);
        virtual void error(const std::string &message);

    protected:
        virtual void log(const std::string &level, const std::string &message);
        virtual void write(const std::string &message) = 0;
    };

}// namespace impress

#endif//IMPRESSHTTP_LOGGER_H
