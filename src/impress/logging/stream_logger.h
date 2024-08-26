#ifndef IMPRESSHTTP_STREAM_LOGGER_H
#define IMPRESSHTTP_STREAM_LOGGER_H

#include "logger.h"

namespace impress {
    class StreamLogger : public Logger {
        std::ostream &m_stream;

    public:
        explicit StreamLogger(std::ostream &stream, LogLevel level = LogLevel::INFO);

    protected:
        void write(const std::string &message) override;
    };
}


#endif//IMPRESSHTTP_STREAM_LOGGER_H
