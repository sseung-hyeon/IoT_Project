#include "WiFiManager.h"
#include "Logger.h"

void WiFiManager::begin()
{
    Logger::info("[WIFI] Initialized");

    // TODO(조립 후):
    // ESP-01 초기화
}

bool WiFiManager::sendPackageInfo(float weightKg)
{
    Logger::info(
        "[MOCK] Send Package Info: " +
        String(weightKg) +
        " kg"
    );

    // TODO(조립 후):
    // Firebase RTDB 업로드

    return true;
}