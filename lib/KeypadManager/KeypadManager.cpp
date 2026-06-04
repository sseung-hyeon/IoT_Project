#include "KeypadManager.h"
#include "Logger.h"

void KeypadManager::begin()
{
    Logger::info("[KEYPAD] Initialized");

    // TODO(조립 후):
    // 실제 Keypad 라이브러리 초기화
}

bool KeypadManager::isPasswordCorrect()
{
    Logger::info("[MOCK] Password Correct");

    // TODO(조립 후):
    // 실제 키패드 입력 검증

    return true;
}