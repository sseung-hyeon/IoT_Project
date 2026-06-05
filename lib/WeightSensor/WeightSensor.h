#ifndef WEIGHT_SENSOR_H
#define WEIGHT_SENSOR_H

#include <Arduino.h>
#include <HX711.h>

class WeightSensor
{
public:
    void begin();

    float getWeightKg();

private:
    // HX711 객체
    HX711 scale;
};

#endif