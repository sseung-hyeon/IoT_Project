#ifndef BUZZER_MANAGER_H
#define BUZZER_MANAGER_H

#include <Arduino.h>

class BuzzerManager
{
public:
    void begin();

    void playSuccessTone();
    void playErrorTone();
    void playAlertTone();

    void startAlertTone();      // ALERT 상태 시작
    void stopAlertTone();       // ALERT 상태 종료
    void updateAlertTone();     // ALERT 반복음 갱신

private:
    // ALERT 동작 여부
    bool alertActive = false;

    // 마지막 경보음 발생 시각
    unsigned long lastAlertTime = 0;
};

#endif