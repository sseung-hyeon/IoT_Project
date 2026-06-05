#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class DisplayManager
{
public:

    DisplayManager();

    // LCD 초기화
    void begin();

    // 대기 화면
    void showIdle();

    // 카드 인증
    void showCardSuccess();
    void showCardFail();

    // 비밀번호 입력
    void showPasswordInput(uint8_t length);

    // 비밀번호 결과
    void showPasswordSuccess();
    void showPasswordFail();

    // 문 상태
    void showDoorOpen();
    void showDoorClose();

    // 경고
    void showAlert();

private:

    // 16x2 I2C LCD
    LiquidCrystal_I2C lcd;
};

#endif