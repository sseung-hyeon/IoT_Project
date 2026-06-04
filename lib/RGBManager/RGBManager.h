#ifndef RGB_MANAGER_H
#define RGB_MANAGER_H

#include <Arduino.h>

class RGBManager
{
public:
    void begin();

    void showNormal();
    void showSuccess();
    void showError();
    void showAlert();
};

#endif