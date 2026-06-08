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

// 카드 존재 여부 확인
bool RFIDManager::isCardPresent()
{
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return false;
    }

    if (!mfrc522.PICC_ReadCardSerial())
    {
        return false;
    }

    return true;
}

bool RFIDManager::isCardDetected()
{
    // 새로운 RFID 카드 감지
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return false;
    }

    // 카드 UID 읽기
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return false;
    }

    Logger::info("[RFID] Card Detected");

    // 등록된 카드인지 확인
    if (!isAuthorizedCard())
    {
        Logger::warn(
            "[RFID] Unauthorized Card"
        );

        // RFID 통신 종료
        // 다음 카드 인식을 위해 정리
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();

        return false;
    }

    Logger::info(
        "[RFID] Authorized Card"
    );

    // RFID 통신 종료
    // 다음 카드 인식을 위해 정리
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    
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

void RFIDManager::endSession()
{
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
}