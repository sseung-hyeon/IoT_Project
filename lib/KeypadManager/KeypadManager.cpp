#include <Keypad.h>

#include "config.h"
#include "KeypadManager.h"
#include "Logger.h"

char keys[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[4] = 
{
    PIN_KEYPAD_R1,
    PIN_KEYPAD_R2,
    PIN_KEYPAD_R3,
    PIN_KEYPAD_R4
};

byte colPins[4] =
{
    PIN_KEYPAD_C1,
    PIN_KEYPAD_C2,
    PIN_KEYPAD_C3,
    PIN_KEYPAD_C4
};

Keypad keypad(
    makeKeymap(keys),
    rowPins,
    colPins,
    4,
    4
);

void KeypadManager::begin()
{
    Logger::info("[KEYPAD] Initialized");

    enteredPassword = "";

    // 비밀번호 상태 초기화
    passwordFailed = false;
}

void KeypadManager::clearInput()
{
    enteredPassword = "";

    lastLength = 0;
}

// MOCK 버전
uint8_t KeypadManager::getInputLength()
{

    return enteredPassword.length(); 
}

bool KeypadManager::isPasswordCorrect()
{
    char key = keypad.getKey();

    if(!key)
    {
        return false;
    }

    Logger::info(
        "[KEYPAD] Pressed : " + 
        String(key)
    );

    // # 입력 시 전체 입력 초기화
    if (key == '#')
    {
        Logger::info(
            "[KEYPAD] Input Cleared"
        );

        clearInput();

        return false;
    }

    // 숫자 입력
    if (key >= '0' && key <= '9')
    {   
        if (enteredPassword.length() < PASSWORD_LENGTH)
        {
            enteredPassword += key;
        }
    }
    // 입력 완료
    if (enteredPassword.length() == PASSWORD_LENGTH)
    {
        Logger::info(
            "[KEYPAD] Input = " + 
            enteredPassword
        );

        // 비밀번호 성공
        if (currentOtp.length() > 0 &&
        enteredPassword == currentOtp)
        {
            clearInput();

            return true;
        }
        // 비밀번호 실패
        Logger::warn(
            "[KEYPAD] Wrong Password"
        );

        passwordFailed = true;

        clearInput();
    }

        return false;
}

bool KeypadManager::hasInputChanged()
{
    uint8_t currentLength = 
        enteredPassword.length();

    if (currentLength != lastLength)
    {
        lastLength = currentLength;

        return true;
    }

    return false;
}

bool KeypadManager::isPasswordFailed()
{
    if (passwordFailed)
    {
        // 한 번 읽으면 자동 초기화
        passwordFailed = false;

        return true;
    }

    return false;
}

// OTP 설정
void KeypadManager::setOtp(
    const String& otp
)
{
    currentOtp = otp;

    Logger::info(
        "[OTP] Set = " + otp
    );
}

// OTP 제거
void KeypadManager::clearOtp()
{
    currentOtp = "";

    Logger::info(
        "[OTP] Cleared"
    );
}

// OTP 존재 여부
bool KeypadManager::hasOtp() const
{
    return currentOtp.length() > 0;
}