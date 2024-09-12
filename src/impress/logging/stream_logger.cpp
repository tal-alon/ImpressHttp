#include "stream_logger.h"

#include <iostream>


StreamLogger::StreamLogger(std::ostream &stream, LogLevel level) : m_stream(stream) {
    m_level = level;
}

void StreamLogger::write(const std::string &message) {
    m_stream << message << std::endl;
}

Logger *StreamLogger::clone() {
    return new StreamLogger(m_stream, m_level);
}
