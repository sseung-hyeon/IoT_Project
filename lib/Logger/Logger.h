#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger
{
public:
    static void info(const String& message);
    static void warn(const String& message);
    static void error(const String& message);
};

#endif