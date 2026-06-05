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

private: 
    String enteredPassword;

    bool passwordFailed = false;

    uint8_t lastLength = 0;

    const String correctPassword = "1234"; // 비밀번호 1234
};

#endif