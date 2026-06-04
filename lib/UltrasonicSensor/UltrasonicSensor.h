#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor
{
public:
    void begin();

    bool hasPackage();
};

#endif