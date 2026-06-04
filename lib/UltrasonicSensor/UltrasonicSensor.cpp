#include "UltrasonicSensor.h"
#include "Logger.h"

void UltrasonicSensor::begin()
{
    Logger::info("[ULTRASONIC] Initialized");

    // TODO(조립 후):
    // pinMode(PIN_TRIG, OUTPUT);
    // pinMode(PIN_ECHO, INPUT);
}

bool UltrasonicSensor::hasPackage()
{
    Logger::info("[MOCK] Package Detected");

    // TODO(조립 후):
    // HC-SR04 거리 측정 구현

    return true;
}