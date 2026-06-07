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

// 대기 화면
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

// 카드 인증
void DisplayManager::showCardSuccess()
{
    Logger::info("[LCD]");
    Logger::info("카드 확인");
    Logger::info("성공");

    // RFID 인증 성공 LCD 표시
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Card Verified");

    lcd.setCursor(0, 1);
    lcd.print("Success");
}

void DisplayManager::showCardFail()
{
    Logger::info("[LCD]");
    Logger::info("카드를");
    Logger::info("다시 태그하세요");

    //RFID 인증 실패 LCD 표시
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Card Failed");

    lcd.setCursor(0, 1);
    lcd.print("Try Again");
}

// 비밀번호 입력
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

    // LCD 비밀번호 입력 표시
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Enter Password");

    lcd.setCursor(0, 1);
    lcd.print(mask);
}

// 비밀번호 결과
void DisplayManager::showPasswordSuccess()
{
    Logger::info("[LCD]");
    Logger::info("비밀번호 확인");
    Logger::info("성공");

    // 비밀번호 인증 성공 LCD 표시
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Password OK");

    lcd.setCursor(0, 1);
    lcd.print("Access Granted");
}

void DisplayManager::showPasswordFail()
{
    Logger::info("[LCD]");
    Logger::info("비밀번호 오류");
    Logger::info("다시 입력");

    // 비밀번호 인증 실패 LCD 표시
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Wrong Password");

    lcd.setCursor(0, 1);
    lcd.print("Try Again");
}

// 문 상태
void DisplayManager::showDoorOpen()
{
    Logger::info("[LCD]");
    Logger::info("문이 열렸습니다");

    // 문 열림 상태 표시
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Door Open");
}

void DisplayManager::showDoorClose()
{
    Logger::info("[LCD]");
    Logger::info("문이 닫혔습니다");

    // 문 닫힘 상태 LCD 표시
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Door Closed");
}

// 경고 상태
void DisplayManager::showAlert()
{
    Logger::info("[LCD]");
    Logger::info("경고!");
    Logger::info("보안 확인 필요!");

    // ALERT 상태 LCD 표시
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("!! WARNING !!");

    lcd.setCursor(0, 1);
    lcd.print("Check Locker");
}