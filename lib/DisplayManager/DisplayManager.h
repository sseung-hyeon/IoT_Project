#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>

class DisplayManager
{
public:
    void begin();

    void showIdle();

    void showCardSuccess();
    void showCardFail();

    void showPasswordInput(uint8_t length);

    void showPasswordSuccess();
    void showPasswordFail();

    void showDoorOpen();
    void showDoorClose();

    void showAlert();
};

#endif