#include "UltrasonicSensor.h"
#include "Logger.h"
#include "config.h"

void UltrasonicSensor::begin()
{
    Logger::info("[ULTRASONIC] Initialized");

    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

bool UltrasonicSensor::hasPackage()
{
    // 초음파 발사
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    // 반사시간 측정
    long duration = pulseIn(PIN_ECHO, HIGH, 30000UL);

    // 초음파 응답 없음
    if (duration == 0)
    {
        Logger::warn(
            "[ULTRASONIC] Timeout"
        );

        return false;
    }

    // 거리 계산
    float distance = duration * 0.034 / 2.0;

    Logger::info(
        "[ULTRASONIC] Distance = " +
        String(distance) +
        " cm"
    );

    // 택배 존재 여부 판단
    if (distance <= PACKAGE_DISTANCE_CM)
    {
        Logger::info(
            "[ULTRASONIC] Package Detected"
        );

        return true;
    }
    return false;
}