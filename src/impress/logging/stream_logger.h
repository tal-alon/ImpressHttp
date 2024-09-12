#pragma once
#include "logger.h"

class StreamLogger : public Logger {
    std::ostream &m_stream;

public:
    explicit StreamLogger(std::ostream &stream, LogLevel level = INFO_LVL);

protected:
    void write(const std::string &message) override;
};
