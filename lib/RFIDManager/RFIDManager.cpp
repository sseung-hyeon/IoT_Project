#include "RFIDManager.h"
#include "Logger.h"

void RFIDManager::begin()
{
    Logger::info("[RFID] Initialized");

    // TODO(조립 후):
    // RC522 초기화
}

bool RFIDManager::isCardDetected()
{
    // Logger::info("[MOCK] RFID Card Detected");
    Serial.println("[MOCK] RFID Card Valid");

    // TODO (조립 후)
    // RC522 UID 읽기

    return true;
}