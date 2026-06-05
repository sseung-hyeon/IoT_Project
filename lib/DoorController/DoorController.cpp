#include "DoorController.h"
#include "Logger.h"
#include "config.h"

void DoorController::begin()
{
    Logger::info("[DOOR] Initialized");

    // ======================================================
    // 서보모터 초기화
    // ======================================================

    servo.attach(PIN_SERVO);

    // 시작 시 잠금 상태
    servo.write(SERVO_LOCK_ANGLE);
}

void DoorController::openDoor()
{
    Logger::info("[MOCK] Door Open");

    // 잠금 해제
    servo.write(SERVO_UNLOCK_ANGLE);
}

void DoorController::closeDoor()
{
    Logger::info("[MOCK] Door Close");

    // 잠금
    servo.write(SERVO_LOCK_ANGLE);
}