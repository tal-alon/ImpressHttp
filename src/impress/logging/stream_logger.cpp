#include "stream_logger.h"

#include <iostream>

using namespace impress;

impress::StreamLogger::StreamLogger(std::ostream &stream, LogLevel level) : m_stream(stream) {
    m_level = level;
}

void impress::StreamLogger::write(const std::string &message) {
    m_stream << message << std::endl;
}
