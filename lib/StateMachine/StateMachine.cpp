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

#include <EEPROM.h>

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
    loadSecuritySettings();
}

void StateMachine::update()
{
    // ESP 명령 수신 처리
    if (wifi.hasIncomingCommand())
    {
        String command =
            wifi.getIncomingCommand();

        // 문 열기
        if (command == "OPEN")
        {
            Logger::info(
                "[APP] OPEN Command"
            );

            changeState(
                LockerState::DOOR_OPEN
            );

            return;
        }

        // 문 닫기
        if (command == "CLOSE")
        {
            Logger::info(
                "[APP] CLOSE Command"
            );

            changeState(
                LockerState::DOOR_CLOSE
            );

            return;
        }

        // ALERT 해제
        if (command == "RESET_ALERT")
        {
            Logger::info(
                "[APP] RESET_ALERT"
            );

            clearAlert();

            return;
        }

        // 상태 요청
        if (command == "STATUS")
        {
            Logger::info(
                "[APP] STATUS Request"
            );

            bool itemPresent =
                ultrasonic.hasPackage()
                ||
                weightSensor.hasPackage();

            wifi.sendStatus(
                currentState ==
                LockerState::DOOR_OPEN,
                itemPresent,
                keypad.hasOtp()
            );

            return;
        }
        // OTP 설정
        if (command.startsWith("OTP:"))
        {
            if (command == "OTP:CANCEL")
            {
                keypad.clearOtp();

                Serial1.println(
                    "OTP:CLEARED"
                );

                if (
                    currentState ==
                    LockerState::AUTH_PIN
                )
                {
                    changeState(
                        LockerState::IDLE
                    );
                }

                return;
            }

            String otp =
                command.substring(4);

            if (otp.length() != PASSWORD_LENGTH)
            {
                Logger::warn(
                    "[OTP] Invalid Length"
                );

                return;
            }

            keypad.setOtp(otp);

            Serial1.println(
                "OTP:READY"
            );

            return;
        }

        // SECURITY 설정
        if (command.startsWith("SECURITY:"))
        {
            String data =
                command.substring(9);

            // SECURITY 형식 검증
            if (
                data.indexOf("SHOCK=") < 0 ||
                data.indexOf("DOOR=") < 0 ||
                data.indexOf("FAIL=") < 0
            )
            {
                Logger::warn(
                    "[SECURITY] Invalid Format"
                );

                return;
            }                

            int shockPos =
                data.indexOf("SHOCK=");

            int doorPos =
                data.indexOf("DOOR=");

            int failPos =
                data.indexOf("FAIL=");

            if (
                shockPos >= 0 &&
                doorPos >= 0 &&
                failPos >= 0
            )
            {
                int shock =
                    data.substring(
                        shockPos + 6,
                        data.indexOf(",", shockPos)
                    ).toInt();

                int door =
                    data.substring(
                        doorPos + 5,
                        data.indexOf(",", doorPos)
                    ).toInt();

                int fail =
                    data.substring(
                        failPos + 5
                    ).toInt();
                
                // SHOCK 범위 확인
                if (
                    shock < 1 ||
                    shock > 20
                )
                {
                    Logger::warn(
                        "[SECURITY] Invalid Shock"
                    );

                    return;
                }

                // DOOR 범위 확인
                if (
                    door < 5 ||
                    door > 300
                )
                {
                    Logger::warn(
                        "[SECURITY] Invalid Door"
                    );

                    return;
                }

                // FAIL 범위 확인
                if (
                    fail < 1 ||
                    fail > 20
                )
                {
                    Logger::warn(
                        "[SECURITY] Invalid Fail"
                    );

                    return;
                }
                
                shockSensor.setShockLimit(
                    shock
                );

                failCounter.setMaxFailCount(
                    fail
                );

                doorOpenLimitMs =
                    (unsigned long)door * 1000UL;

                saveSecuritySettings();

                Serial1.println(
                    "SECURITY:UPDATED"
                );

                Logger::info(
                    "[SECURITY] Updated"
                );

                Logger::info(
                    "Shock=" +
                    String(shock)
                );

                Logger::info(
                    "Door=" +
                    String(door)
                );

                Logger::info(
                    "Fail=" +
                    String(fail)
                );
            }

            return;
        }
    }

    // ALERT 반복음 갱신
    buzzer.updateAlertTone();

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

    if (rfid.isCardPresent())
    {
        // 등록 카드
        if (rfid.isAuthorizedCard())
        {
            Logger::info(
                "[FSM] RFID Success"
            );

            buzzer.playSuccessTone();
            rgb.showSuccess();
            display.showCardSuccess();

            rfid.endSession();

            changeState(
                LockerState::AUTH_PIN
            );

            return;
        }

        Logger::warn(
            "[RFID] Unauthorized Card"
        );

        failCounter.increase();

        buzzer.playErrorTone();

        display.showCardFail();

        rgb.showError();

        Logger::warn(
            "[AUTH] Fail Count = " +
            String(failCounter.getCount())
        );

        rfid.endSession();

        if (failCounter.isLimitReached())
        {
            changeState(
                LockerState::ALERT
            );
        }

        return;
    }
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

        keypad.clearOtp();

        Serial1.println(
            "OTP:USED"
        );
        
        changeState(LockerState::DOOR_OPEN);

        return;
    }

    // 비밀번호 실패 처리
    if (keypad.isPasswordFailed())
    {
        Logger::warn("[AUTH] Password Failed");

        // 실패 횟수 증가
        failCounter.increase();

        // 실패 알림
        buzzer.playErrorTone();

        // LCD 표시
        display.showPasswordFail();

        rgb.showError();

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
            
            wifi.uploadDoorStatus(true);

            doorOpenStartTime = millis(); // 문 열림 시작 시각 저장

            stateJustEntered = false;

            return;
        }
        
        //문을 일정시간 열어둠
        if (millis() - doorOpenStartTime > doorOpenLimitMs)
            {
                Logger::info("[FSM] Door Open Timeout");

                changeState(LockerState::MEASURE);
            }
}

// 택배 존재 여부 확인
// 초음파 + 무게센서
void StateMachine::handleMeasure()
{
    if (stateJustEntered)
    {
        Logger::info("[FSM] Enter MEASURE");

        stateJustEntered = false;

        if (ultrasonic.hasPackage() || weightSensor.hasPackage())
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
        else
        {
            Logger::warn(
                "[FSM] Package Not Detected"
            );

            changeState(LockerState::DOOR_CLOSE);
        }
    }
}

// 택배 정보 전송
// MQTT/ESP 전송 후 문 닫힘 상태로 이동
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

        wifi.uploadDoorStatus(false);

        changeState(LockerState::IDLE);
    }
}

void StateMachine::handleAlert()
{
    if (stateJustEntered)
    {
        Logger::error("[FSM] Enter ALERT");

        failCounter.reset();

        buzzer.startAlertTone();

        rgb.showAlert();

        display.showAlert();

        wifi.uploadAlertStatus(true);

        stateJustEntered = false;
    }
}

void StateMachine::clearAlert()
{
    Logger::info("[FSM] ALERT Cleared");

    buzzer.stopAlertTone();

    wifi.uploadAlertStatus(false);

    wifi.clearAlertRequest();

    changeState(LockerState::IDLE);
}

void StateMachine::saveSecuritySettings()
{
    SecuritySettings settings;

    settings.shockLimit =
        shockSensor.getShockLimit();

    settings.maxFailCount =
        failCounter.getMaxFailCount();

    settings.doorOpenLimitMs =
        doorOpenLimitMs;

    EEPROM.put(
        0,
        settings
    );

    Logger::info(
        "[EEPROM] Security Saved"
    );
}

void StateMachine::loadSecuritySettings()
{
    SecuritySettings settings;

    EEPROM.get(
        0,
        settings
    );

    // 초기 EEPROM 방어
    if (
        settings.shockLimit < 1 ||
        settings.shockLimit > 20
    )
    {
        Logger::warn(
            "[EEPROM] Default Security"
        );

        return;
    }

    shockSensor.setShockLimit(
        settings.shockLimit
    );

    failCounter.setMaxFailCount(
        settings.maxFailCount
    );

    doorOpenLimitMs =
        settings.doorOpenLimitMs;

    Logger::info(
        "[EEPROM] Security Loaded"
    );
}