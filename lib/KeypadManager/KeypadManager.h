#ifndef KEYPAD_MANAGER_H
#define KEYPAD_MANAGER_H

#include <Arduino.h>

class KeypadManager
{
public:
    void begin();

    bool isPasswordCorrect();
    bool hasInput();
};

#endif