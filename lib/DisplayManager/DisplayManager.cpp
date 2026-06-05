#include "DisplayManager.h"
#include "Logger.h"
#include "config.h"

#include <LiquidCrystal_I2C.h>

DisplayManager::DisplayManager()
    : lcd(LCD_I2C_ADDRESS, 16, 2)
{

}

void DisplayManager::begin()
{
    Logger::info("[DISPLAY] Initialized");

    lcd.init();
    lcd.backlight();

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Smart Locker");
}

// ======================================================
// 대기 화면
// ======================================================

void DisplayManager::showIdle()
{
    Logger::info("[LCD]");
    Logger::info("Smart Locker");
    Logger::info("카드를 태그하세요");

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Smart Locker");

    lcd.setCursor(0, 1);
    lcd.print("Tag Card");
}

// ======================================================
// 카드 인증
// ======================================================

void DisplayManager::showCardSuccess()
{
    Logger::info("[LCD]");
    Logger::info("카드 확인");
    Logger::info("성공");
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

    for (uint8_t i = 0; i < PASSWORD_LENGTH; i++)
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
    Logger::info("성공");
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
    Logger::info("문이 닫혔습니다");
}

// ======================================================
// 경고 상태
// ======================================================

void DisplayManager::showAlert()
{
    Logger::info("[LCD]");
    Logger::info("경고!");
    Logger::info("보안 확인 필요!");
}