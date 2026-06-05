#ifndef RGB_MANAGER_H
#define RGB_MANAGER_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class RGBManager
{
public:
    RGBManager();

    void begin();

    void showNormal();
    void showSuccess();
    void showError();
    void showAlert();

private:
    Adafruit_NeoPixel pixels;
};

#endif