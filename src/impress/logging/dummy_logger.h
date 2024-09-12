#pragma once

#include "logger.h"

class DummyLogger : public Logger {
public:
    Logger *clone() override { return new DummyLogger(); }
protected:
    void write(const std::string &message) override {}
};
