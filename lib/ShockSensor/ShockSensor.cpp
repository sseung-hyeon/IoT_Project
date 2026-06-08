#include "ShockSensor.h"
#include "Logger.h"
#include "config.h"


void ShockSensor::begin()
{
    Logger::info("[SHOCK] Initialized");

    pinMode(PIN_SHOCK, INPUT_PULLUP);
}

bool ShockSensor::isShockDetected()
{
    // 충격 감지
    if (digitalRead(PIN_SHOCK) == LOW)
    {
        delay(SHOCK_DEBOUNCE_MS);

        if (digitalRead(PIN_SHOCK) == LOW)
        {
            unsigned long now = millis();

            // 시간창 초기화
            if (
                now - shockWindowStart >
                SHOCK_WINDOW_MS
            )
            {
                shockWindowStart = now;
                shockCount = 0;
            }

            shockCount++;

            Logger::warn(
                "[SHOCK] Count = " +
                String(shockCount)
            );

            // 제한 횟수 초과
            if (shockCount >= shockLimit)
            {
                Logger::error(
                    "[SHOCK] ALERT Triggered"
                );

                shockCount = 0;

                return true;
            }

            delay(50);
        }
    }

    return false;
}

void ShockSensor::setShockLimit(int value)
{
    shockLimit = value;
}

int ShockSensor::getShockLimit() const
{
    return shockLimit;
}