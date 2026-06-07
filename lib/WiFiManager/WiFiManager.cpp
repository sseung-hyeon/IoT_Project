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
        "weightKg = " +
        String(weightKg)
    );

    // ESP에 택배 무게 전송
    Serial1.println(
        "PACKAGE:" +
        String(weightKg, 2)
    );

    return true;
}

bool WiFiManager::isAlertClearRequested()
{
    return false;
}

bool WiFiManager::uploadAlertStatus(bool alert)
{
    Logger::info(
        "[WIFI] Alert Status = " +
        String(alert)
    );

    // ALERT 상태 전송
    if (alert)
    {
        Serial1.println(
            "ALERT:SHOCK"
        );
    }

        return true;
    }

bool WiFiManager::uploadDoorStatus(bool open)
{
    Logger::info(
        "[WIFI] Door Status = " +
        String(open)
    );

    // 문 상태 전송
    if (open)
    {
        Serial1.println(
            "STATE:OPEN"
        );
    }
    else
    {
        Serial1.println(
            "STATE:CLOSED"
        );
    }

    return true;
}

// Firebase clearAlert 초기화
bool WiFiManager::clearAlertRequest()
{
    Logger::info(
        "[WIFI] Clear Alert Reset"
    );

    return true;
}

// ESP 명령 수신 여부 확인
bool WiFiManager::hasIncomingCommand()
{
    return Serial1.available() > 0;
}

// ESP 명령 읽기
String WiFiManager::getIncomingCommand()
{
    String command =
        Serial1.readStringUntil('\n');

    command.trim();

    Logger::info(
        "[WIFI] RX : " +
        command
    );

    return command;
}