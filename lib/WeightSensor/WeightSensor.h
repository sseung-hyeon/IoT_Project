#ifndef WEIGHT_SENSOR_H
#define WEIGHT_SENSOR_H

#include <Arduino.h>

class WeightSensor
{
public:
    void begin();

    float getWeightKg();
};

#endif