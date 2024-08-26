#pragma once
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
