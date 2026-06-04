#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

class WiFiManager
{
public:
    void begin();

    bool sendPackageInfo(float weightKg);
};

#endif