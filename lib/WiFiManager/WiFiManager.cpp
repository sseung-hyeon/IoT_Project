#include "WiFiManager.h"
#include "Logger.h"
#include "config.h"

void WiFiManager::begin()
{
    Logger::info("[WIFI] Initialized");

    // ESP-01S UART 연결
    // Mega TX1(D18) -> ESP RX
    // Mega RX1(D19) -> ESP TX

    // ESP-01S 연결 포트
    Serial1.begin(ESP_BAUDRATE);
    
    Logger::info("[WIFI] Serial1 Ready");

    // ESP에게 명령 전송
    Serial1.println("AT");

    // ESP 응답 확인
    delay(1000);

    while (Serial1.available()) // ESP가 답장을 보냈는지 확인
    {
        char c = Serial1.read();

        Serial.write(c); // 답장을 시리얼 모니터로 출력
    }
}

bool WiFiManager::sendPackageInfo(float weightKg)
{
    Logger::info(
        "[WIFI] Package Upload Request"
    );

    Logger::info(
    "[FIREBASE] Upload Package"
    );

    Logger::info(
        "Path : " +
        String(FIREBASE_LOCKER_PATH)
    );

    Logger::info(
        "weightKg = " +
        String(weightKg)
    );

    Logger::info(
        "packageDetected = true"
    );

    return true;
}

bool WiFiManager::isAlertClearRequested()
{
    // 조립후 파이어베이스 값 확인

    return false;
}

// Firebase ALERT 상태 업로드

bool WiFiManager::uploadAlertStatus(bool alert)
{
    Logger::info(
        "[WIFI] Alert Status = " +
        String(alert)
    );

    Logger::info(
    "Firebase Key : " +
    String(FIREBASE_KEY_ALERT)
    );

    return true;
}

// Firebase 문 상태 업로드
bool WiFiManager::uploadDoorStatus(bool open)
{
    Logger::info(
        "[WIFI] Door Status = " +
        String(open)
    );

    Logger::info(
    "Firebase Key : " +
    String(FIREBASE_KEY_DOOR)
    );

    // TODO(ESP + Firebase 구현 후)
    // Firebase /locker/doorOpen 업데이트

    return true;
}

// Firebase clearAlert 초기화
bool WiFiManager::clearAlertRequest()
{
    Logger::info(
        "[WIFI] Clear Alert Reset"
    );

    Logger::info(
    "Firebase Key : " +
    String(FIREBASE_KEY_CLEAR_ALERT)
    );

    Logger::info(
        "Value : false"
    );
    // TODO(ESP + Firebase 구현 후)
    // Firebase /locker/clearAlert = false

    return true;
}