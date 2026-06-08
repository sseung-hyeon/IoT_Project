#ifndef KEYPAD_MANAGER_H
#define KEYPAD_MANAGER_H

#include <Arduino.h>

class KeypadManager
{
public:
    void begin();

    bool isPasswordCorrect();

    bool isPasswordFailed();

    uint8_t getInputLength();

    void clearInput();

    bool hasInputChanged();

    // 앱에서 전달받은 OTP 설정
    void setOtp(const String& otp);

    // OTP 제거
    void clearOtp();

    // OTP 존재 여부
    bool hasOtp() const;

private: 
    String enteredPassword;

    bool passwordFailed = false;

    uint8_t lastLength = 0;

    // 현재 활성 OTP
    String currentOtp = "";
};

#endif