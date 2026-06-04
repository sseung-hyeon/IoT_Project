#include "DisplayManager.h"
#include "Logger.h"

void DisplayManager::begin()
{
    Logger::info("[DISPLAY] Initialized");

    // TODO(조립 후)
    // lcd.init();
    // lcd.backlight();
}

// ======================================================
// 대기 화면
// ======================================================

void DisplayManager::showIdle()
{
    Logger::info("[LCD]");
    Logger::info("Smart Locker");
    Logger::info("카드를 태그하세요");
}

// ======================================================
// 카드 인증
// ======================================================

void DisplayManager::showCardSuccess()
{
    Logger::info("[LCD]");
    Logger::info("카드 확인 완료");
    Logger::info("비밀번호 입력");
}

void DisplayManager::showCardFail()
{
    Logger::info("[LCD]");
    Logger::info("카드를");
    Logger::info("다시 태그하세요");
}

// ======================================================
// 비밀번호 입력
// ======================================================

void DisplayManager::showPasswordInput(uint8_t length)
{
    String mask = "";

    for (uint8_t i = 0; i < 4; i++)
    {
        if (i < length)
        {
            mask += "*";
        }
        else
        {
            mask += "-";
        }
    }

    Logger::info("[LCD]");
    Logger::info("비밀번호 입력");
    Logger::info(mask);
}

// ======================================================
// 비밀번호 결과
// ======================================================

void DisplayManager::showPasswordSuccess()
{
    Logger::info("[LCD]");
    Logger::info("비밀번호 확인");
    Logger::info("완료");
}

void DisplayManager::showPasswordFail()
{
    Logger::info("[LCD]");
    Logger::info("비밀번호 오류");
    Logger::info("다시 입력");
}

// ======================================================
// 문 상태
// ======================================================

void DisplayManager::showDoorOpen()
{
    Logger::info("[LCD]");
    Logger::info("문이 열렸습니다");
}

void DisplayManager::showDoorClose()
{
    Logger::info("[LCD]");
    Logger::info("문을 닫습니다");
}

// ======================================================
// 경고 상태
// ======================================================

void DisplayManager::showAlert()
{
    Logger::info("[LCD]");
    Logger::info("경고!");
    Logger::info("충격 감지");
}