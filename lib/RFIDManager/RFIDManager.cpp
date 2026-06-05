#include <SPI.h>
#include <MFRC522.h>

#include "config.h"
#include "Logger.h"
#include "RFIDManager.h"

static MFRC522 mfrc522(
    PIN_RFID_SS,
    PIN_RFID_RST
);

void RFIDManager::begin()
{
    SPI.begin();

    mfrc522.PCD_Init();

    Logger::info("[RFID] Initialized");

    // TODO(조립 후):
    // RC522 초기화
}

bool RFIDManager::isCardDetected()
{
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return false;
    }

    if (!mfrc522.PICC_ReadCardSerial())
    {
        return false;
    }

    Logger::info("[RFID] Card Detected");

    return true;

    #if MOCK_AUTO_SUCCESS // MOCK 
        return true;
    #endif
}

// TODO(하드웨어 연결 후)
//
// #include <SPI.h>
// #include <MFRC522.h>
//
// MFRC522 mfrc522(PIN_RFID_SS, PIN_RFID_RST);
//
// begin()
// {
//     SPI.begin();
//     mfrc522.PCD_Init();
// }
//
// isCardDetected()
// {
//     return mfrc522.PICC_IsNewCardPresent()
//         && mfrc522.PICC_ReadCardSerial();
// }