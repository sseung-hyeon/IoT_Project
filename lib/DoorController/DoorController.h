#ifndef DOOR_CONTROLLER_H
#define DOOR_CONTROLLER_H

#include <Arduino.h>

class DoorController
{
public:
    void begin();

    void openDoor();
    void closeDoor();
};

#endif