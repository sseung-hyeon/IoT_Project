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
        // 노이즈 제거를 위해 20ms 후 재확인
        delay(SHOCK_DEBOUNCE_MS);

        if (digitalRead(PIN_SHOCK) == LOW)
        {
            Logger::warn("[SHOCK] Shock Detected");

            return true;
        }
    }    

    return false;
}