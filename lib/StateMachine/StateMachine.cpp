#include "StateMachine.h"
#include "Logger.h"
#include "RFIDManager.h"
#include "KeypadManager.h"
#include "DoorController.h"
#include "UltrasonicSensor.h"
#include "WeightSensor.h"
#include "WiFiManager.h"
#include "ShockSensor.h"
#include "BuzzerManager.h"
#include "RGBManager.h"
#include "DisplayManager.h"
#include "FailCounter.h"


static RFIDManager rfid;
static KeypadManager keypad;
static DoorController door;
static UltrasonicSensor ultrasonic;
static WeightSensor weightSensor;
static WiFiManager wifi;
static ShockSensor shockSensor;
static BuzzerManager buzzer;
static RGBManager rgb;
static DisplayManager display;
static FailCounter failCounter;


StateMachine::StateMachine()
{
    currentState = LockerState::IDLE;
    stateJustEntered = true;
    lastMeasuredWeight = 0.0f;
    authStartTime = 0;
    doorOpenStartTime = 0;
}

void StateMachine::begin()
{
    Logger::info("[FSM] Initialized");

    rfid.begin();
    keypad.begin();
    door.begin();
    ultrasonic.begin();
    weightSensor.begin();
    wifi.begin();
    shockSensor.begin();
    buzzer.begin();
    rgb.begin();
    display.begin();
    failCounter.reset();
}

void StateMachine::update()
{
    if (currentState != LockerState::ALERT && 
        shockSensor.isShockDetected())
    {
        Logger::error("[ALERT] Shock Detected"); 

        changeState(LockerState::ALERT);

        return;
    }

    switch (currentState)
    {
    case LockerState::IDLE:
        handleIdle();
        break;

    case LockerState::AUTH_CARD:
        handleAuthCard();
        break;

    case LockerState::AUTH_PIN:
        handleAuthPin();
        break;

    case LockerState::DOOR_OPEN:
        handleDoorOpen();
        break;

    case LockerState::MEASURE:
        handleMeasure();
        break;

    case LockerState::NOTIFY:
        handleNotify();
        break;

    case LockerState::DOOR_CLOSE:
        handleDoorClose();
        break;

    case LockerState::ALERT:
        handleAlert();
        break;
    }
}

LockerState StateMachine::getCurrentState() const
{
    return currentState;
}

void StateMachine::changeState(LockerState newState)
{
    currentState = newState;

    stateJustEntered = true;

    Logger::info(
        "[FSM] Change State -> " + 
        String(stateToString(newState))
    );
}

const char* StateMachine::stateToString(LockerState state)
{
    switch (state)
    {
    case LockerState::IDLE:
        return "IDLE";

    case LockerState::AUTH_CARD:
        return "AUTH_CARD";

    case LockerState::AUTH_PIN:
        return "AUTH_PIN";

    case LockerState::DOOR_OPEN:
        return "DOOR_OPEN";

    case LockerState::MEASURE:
        return "MEASURE";

    case LockerState::NOTIFY:
        return "NOTIFY";

    case LockerState::DOOR_CLOSE:
        return "DOOR_CLOSE";

    case LockerState::ALERT:
        return "ALERT";

    default:
        return "UNKNOWN";
    }
}

void StateMachine::handleIdle()
{
    if (stateJustEntered)
    {
        Logger::info("[FSM] Enter IDLE");

        rgb.showNormal();
        display.showIdle();

        stateJustEntered = false;

        #if MOCK_AUTO_SUCCESS
            changeState(LockerState::AUTH_CARD);
        #endif
    }
}

void StateMachine::handleAuthCard()
{
    if (stateJustEntered)
    {
        Logger::info("[FSM] Enter AUTH_CARD");

        stateJustEntered = false;
    }

    if (rfid.isCardDetected())
    {
        Logger::info("[FSM] RFID Success");

        buzzer.playSuccessTone();
        rgb.showSuccess();
        display.showCardSuccess();

        changeState(LockerState::AUTH_PIN);
    }
    // TODO(조립 후)
    //
    // 카드 인식 실패 시
    //
    // failCounter.increase();
    //
    // display.showCardFail();
    //
    // buzzer.playErrorTone();
    //
    // if (failCounter.isLimitReached())
    // {
    //     changeState(LockerState::ALERT);
    // }
}

void StateMachine::handleAuthPin()
{
    if (stateJustEntered)
    {
        Logger::info("[FSM] Enter AUTH_PIN");

        display.showPasswordInput(0);

        authStartTime = millis();

        stateJustEntered = false;
    }

    // 입력 표시
    if (keypad.hasInputChanged())
        {
            display.showPasswordInput(
                keypad.getInputLength()
            );
        }
        

    if (millis() - authStartTime > AUTH_TIMEOUT_MS)
    {
        Logger::warn("[AUTH] Timeout");

        changeState(LockerState::IDLE);

        return;
    }

    if (keypad.isPasswordCorrect())
    {
        Logger::info("[FSM] Password Success");

        buzzer.playSuccessTone();
        rgb.showSuccess();
        display.showPasswordSuccess();

        failCounter.reset();

        changeState(LockerState::DOOR_OPEN);

        return;
    }

    // ======================================================
    // 비밀번호 실패 처리
    // ======================================================
    if (keypad.isPasswordFailed())
    {
        Logger::warn("[AUTH] Password Failed");

        // 실패 횟수 증가
        failCounter.increase();

        // 실패 알림
        buzzer.playErrorTone();

        // LCD 표시
        display.showPasswordFail();

        // 실패 횟수 출력
        Logger::warn(
            "[AUTH] Fail Count = " +
            String(failCounter.getCount())
        );

        // 5회 이상 실패
        if (failCounter.isLimitReached())
        {
            Logger::error(
                "[AUTH] Too Many Failures"
            );

            changeState(
                LockerState::ALERT
            );
        }

        return;
    }
}

void StateMachine::handleDoorOpen()
{
    if (stateJustEntered)
        {
            Logger::info("[FSM] Enter DOOR_OPEN");

            door.openDoor();

            display.showDoorOpen();

            doorOpenStartTime = millis(); // 문 열림 시작 시각 저장

            stateJustEntered = false;

            return;
        }
        
        //문을 일정시간 열어둠
        if (millis() - doorOpenStartTime > DOOR_OPEN_TIMEOUT_MS)
            {
                Logger::info("[FSM] Door Open Timeout");

                changeState(LockerState::MEASURE);
            }
}

void StateMachine::handleMeasure()
{
    if (stateJustEntered)
    {
        Logger::info("[FSM] Enter MEASURE");

        stateJustEntered = false;

        if (ultrasonic.hasPackage())
        {
            Logger::info("[FSM] Package Confirmed");

            lastMeasuredWeight = weightSensor.getWeightKg();

            Logger::info(
                "[FSM] Weight = " +
                String(lastMeasuredWeight) + 
                " kg"
            );

            changeState(LockerState::NOTIFY);
        }
    }
}

void StateMachine::handleNotify()
{
    if (stateJustEntered)
    {
        Logger::info("[FSM] Enter NOTIFY");

        stateJustEntered = false;

        if (wifi.sendPackageInfo(lastMeasuredWeight))
        {
            Logger::info("[FSM] Notification Sent");

            changeState(LockerState::DOOR_CLOSE);
        }
    }
}

void StateMachine::handleDoorClose()
{
    if (stateJustEntered)
    {    
        Logger::info("[FSM] Enter DOOR_CLOSE");
        
        stateJustEntered = false;

        door.closeDoor();
        display.showDoorClose();

        changeState(LockerState::IDLE);
    }
}

void StateMachine::handleAlert()
{
    if (stateJustEntered)
    {
        Logger::error("[FSM] Enter ALERT");

        failCounter.reset();
        buzzer.playAlertTone();
        rgb.showAlert();
        display.showAlert();

        stateJustEntered = false;
    }

    // TODO(조립 후)
    // 등록된 RFID 카드 태그 또는
    // 앱 원격 해제 명령 수신 시
    // clearAlert() 호출
}

void StateMachine::clearAlert()
{
    Logger::info("[FSM] ALERT Cleared");

    changeState(LockerState::IDLE);
}
