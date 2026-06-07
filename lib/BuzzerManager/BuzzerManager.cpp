#include "BuzzerManager.h"
#include "Logger.h"
#include "config.h"

void BuzzerManager::begin()
{
    Logger::info("[BUZZER] Initialized");

    pinMode(PIN_BUZZER, OUTPUT);
}

void BuzzerManager::playSuccessTone()
{
    Logger::info("[BUZZER] Success Tone");

    // 인증 성공
    tone(PIN_BUZZER, 1500, 80);
    delay(100);

    tone(PIN_BUZZER, 2000, 80);
    delay(100);

    tone(PIN_BUZZER, 2600, 120);
}

void BuzzerManager::playErrorTone()
{
    Logger::info("[BUZZER] Error Tone");

    // 인증 실패
    tone(PIN_BUZZER, 500, 600);
}

void BuzzerManager::playAlertTone()
{
    Logger::info("[BUZZER] Alert Tone");

    // 경보음
    for (int i = 0; i < 5; i++)
    {
        tone(PIN_BUZZER, 3000, 1000);
    }
}

// Alert 시작
void BuzzerManager::startAlertTone()
{
    alertActive = true;

    Logger::warn("[BUZZER] Alert Started");
}

//Alert 종료
void BuzzerManager::stopAlertTone()
{
    alertActive = false;

    noTone(PIN_BUZZER);

    Logger::info("[BUZZER] Alert Stopped");
}

// ALERT 반복음
void BuzzerManager::updateAlertTone()
{
    // ALERT 상태가 아니면 종료
    if (!alertActive)
    {
        return;
    }

    // 300ms마다 경보음 출력
    if (millis() - lastAlertTime > 300)
    {
        tone(
            PIN_BUZZER,
            3000,   // 3kHz
            150     // 0.15초
        );

        lastAlertTime = millis();
    }
}