#ifndef RFID_MANAGER_H
#define RFID_MANAGER_H

#include <Arduino.h>

class RFIDManager
{
public:
    void begin();

    bool isCardDetected();

private:
    bool mockDetected;

    bool isAuthorizedCard();
};

#endif