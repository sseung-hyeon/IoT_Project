#include "BuzzerManager.h"
#include "Logger.h"

void BuzzerManager::begin()
{
    Logger::info("[BUZZER] Initialized");

    // TODO(조립 후):
    // pinMode(PIN_BUZZER, OUTPUT);
}

void BuzzerManager::playSuccessTone()
{
    Logger::info("[MOCK] Success Tone");

    // TODO(조립 후):
    // tone(PIN_BUZZER, 2000, 100);
}

void BuzzerManager::playErrorTone()
{
    Logger::info("[MOCK] Error Tone");

    // TODO(조립 후):
    // tone(PIN_BUZZER, 800, 300);
}

void BuzzerManager::playAlertTone()
{
    Logger::info("[MOCK] Alert Tone");

    // TODO(조립 후):
    // tone(PIN_BUZZER, 3000, 1000);
}