#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>
#include <config.h>

// FSM 상태 정의
enum class LockerState
{
    IDLE,
    AUTH_CARD,
    AUTH_PIN,
    DOOR_OPEN,
    MEASURE,
    NOTIFY,
    DOOR_CLOSE,
    ALERT
};

class StateMachine
{
public:
    StateMachine();

    void begin();
    void update();

    LockerState getCurrentState() const;
    
    void changeState(LockerState newState);

    const char* stateToString(LockerState state);

private:
    LockerState currentState;
    bool stateJustEntered;
    float lastMeasuredWeight;
    unsigned long authStartTime; // 인증 타임아웃 측정용
    unsigned long doorOpenStartTime; // 문 열림 유지 시간 측정용
    // 앱에서 변경 가능한 문 열림 제한시간
    unsigned long doorOpenLimitMs = DOOR_OPEN_TIMEOUT_MS;

    void handleIdle();
    void handleAuthCard();
    void handleAuthPin();
    void handleDoorOpen();
    void handleMeasure();
    void handleNotify();
    void handleDoorClose();
    void handleAlert();
    void clearAlert();


};

#endif
