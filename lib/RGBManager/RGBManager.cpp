#include "RGBManager.h"
#include "Logger.h"

void RGBManager::begin()
{
    Logger::info("[RGB] Initialized");

    // TODO(조립 후):
    // NeoPixel.begin();
}

void RGBManager::showNormal()
{
    Logger::info("[MOCK] RGB NORMAL (BLUE)");

    // TODO(조립 후):
    // 파랑 LED 출력
}

void RGBManager::showSuccess()
{
    Logger::info("[MOCK] RGB SUCCESS (GREEN)");

    // TODO(조립 후):
    // 초록 LED 출력
}

void RGBManager::showError()
{
    Logger::info("[MOCK] RGB ERROR (RED BLINK)");

    // TODO(조립 후):
    // 빨강 3회 점멸
}

void RGBManager::showAlert()
{
    Logger::info("[MOCK] RGB ALERT (RED FLASH)");

    // TODO(조립 후):
    // 빨강 지속 점멸
}