#ifndef RFID_MANAGER_H
#define RFID_MANAGER_H

#include <Arduino.h>

class RFIDManager
{
public:
    void begin();

    bool isCardDetected();

    bool isCardPresent();

private:
    bool mockDetected;

    bool isAuthorizedCard();
};

#endif