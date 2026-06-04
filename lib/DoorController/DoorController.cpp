#include "DoorController.h"
#include "Logger.h"

void DoorController::begin()
{
    Logger::info("[DOOR] Initialized");

    //TODO(조립 후):
    // Servo.attach(PIN_SERVO);
}

void DoorController::openDoor()
{
    Logger::info("[MOCK] Door Open");

    // TODO(조립 후):
    // servo.write(SERVO_UNLOCK_ANGLE);
}

void DoorController::closeDoor()
{
    Logger::info("[MOCK] Door Close");

    // TODO(조립 후):
    // servo.write(SERVO_LOCK_ANGLE);
}