#include "WeightSensor.h"
#include "Logger.h"

void WeightSensor::begin()
{
    Logger::info("[WEIGHT] Initialized");

    // TODO(조립 후):
    // HX711 초기화
}

float WeightSensor::getWeightKg()
{
    Logger::info("[MOCK] Weight Read");

    // TODO(조립 후):
    // HX711 실제 무게 측정

    return 0.75f;
}