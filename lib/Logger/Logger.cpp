#include "Logger.h"

void Logger::info(const String& message)
{
    Serial.print("[INFO ]");
    Serial.println(message);
}

void Logger::warn(const String& message)
{
    Serial.print("[WARN ]");
    Serial.println(message);
}

void Logger::error(const String& message)
{
    Serial.print("[ERROR] ");
    Serial.println(message);
}