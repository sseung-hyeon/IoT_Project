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
};

#endif