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
    Logger::info("[RFID] Card Detected");

    // 등록된 카드인지 확인
    if (!isAuthorizedCard())
    {
        Logger::warn(
            "[RFID] Unauthorized Card"
        );

        return false;
    }

    Logger::info(
        "[RFID] Authorized Card"
    );

    return true;    
}

// 등록된 카드 UID 확인
bool RFIDManager::isAuthorizedCard()
{
    if (mfrc522.uid.size < 4)
    {
        return false;
    }

    return
        mfrc522.uid.uidByte[0] == RFID_UID_0 &&
        mfrc522.uid.uidByte[1] == RFID_UID_1 &&
        mfrc522.uid.uidByte[2] == RFID_UID_2 &&
        mfrc522.uid.uidByte[3] == RFID_UID_3;
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