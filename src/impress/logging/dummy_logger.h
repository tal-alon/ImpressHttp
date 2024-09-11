#pragma once

#include "logger.h"

class DummyLogger : public Logger {
protected:
    void write(const std::string &message) override {}
};
