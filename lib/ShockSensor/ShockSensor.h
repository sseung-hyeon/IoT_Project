#ifndef SHOCK_SENSOR_H
#define SHOCK_SENSOR_H

#include <Arduino.h>

class ShockSensor
{
public:
    void begin();

    bool isShockDetected();

private:

};

#endif