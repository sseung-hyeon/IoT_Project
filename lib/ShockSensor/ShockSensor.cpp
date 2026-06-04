#include "ShockSensor.h"
#include "Logger.h"

void ShockSensor::begin()
{
    Logger::info("[SHOCK] Initialized");

    // TODO(조립 후):
    // pinMode(PIN_SHOCK, INPUT_PULLUP);
    // attachInterrupt(...)
}

bool ShockSensor::isShockDetected()
{
    // TODO(조립 후):
    // 실제 충격 감지 구현

    return false;
}