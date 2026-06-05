#ifndef SHOCK_SENSOR_H
#define SHOCK_SENSOR_H

#include <Arduino.h>

class ShockSensor
{
public:
    void begin();

    bool isShockDetected();

private:
    // 충격 발생 여부 저장
        volatile bool shockDetected = false;
};

#endif