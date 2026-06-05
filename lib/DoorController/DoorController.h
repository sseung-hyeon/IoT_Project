#ifndef DOOR_CONTROLLER_H
#define DOOR_CONTROLLER_H

#include <Arduino.h>
#include <Servo.h>

class DoorController
{
public:
    void begin();

    void openDoor();
    void closeDoor();

private:

    // SG90 서보 객체
    Servo servo;
};

#endif