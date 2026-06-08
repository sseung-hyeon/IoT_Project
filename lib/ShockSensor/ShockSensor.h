#ifndef SHOCK_SENSOR_H
#define SHOCK_SENSOR_H

#include <Arduino.h>

class ShockSensor
{
public:
    void begin();

    bool isShockDetected();

    void setShockLimit(int value);

    int getShockLimit() const;

private:
    // 충격 누적 카운트
    int shockCount = 0;

    // 충격 감지 시간 측정
    unsigned long shockWindowStart = 0;

    // 충격 판정 시간창
    static const unsigned long SHOCK_WINDOW_MS = 3000UL;

    // ALERT 발생 충격 횟수
    int shockLimit = 5;
};

#endif