#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

class WiFiManager
{
public:
    void begin();

    // 택배 정보 전송
    bool sendPackageInfo(float weightKg);

    // ALERT 원격 해제 여부 확인
    bool isAlertClearRequested();

    // ESP 명령 수신 여부 확인
    bool hasIncomingCommand();

    // ESP 명령 읽기
    String getIncomingCommand();

    
    // Firebase 상태 업로드

    // 경보 상태 업로드
    bool uploadAlertStatus(bool alert);

    // 문 상태 업로드
    bool uploadDoorStatus(bool open);

    // 앱 clearAlert 플래그 초기화
    bool clearAlertRequest(); 
};

#endif