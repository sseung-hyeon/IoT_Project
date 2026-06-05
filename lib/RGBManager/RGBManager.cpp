#include "RGBManager.h"
#include "Logger.h"
#include "config.h"

RGBManager::RGBManager()
    : pixels(
        NUM_PIXELS,
        PIN_NEOPIXEL,
        NEO_GRB + NEO_KHZ800
    )
{

}

void RGBManager::begin()
{
    Logger::info("[RGB] Initialized");

    pixels.begin();
    pixels.clear();
    pixels.show();
}

void RGBManager::showNormal()
{
    Logger::info("[RGB] NORMAL");

    pixels.clear();

}

void RGBManager::showSuccess()
{
    Logger::info("[RGB] SUCCESS");

    pixels.clear();

    pixels.setPixelColor(
        0,
        pixels.Color(0,255,0)
    );

    pixels.show();
}

void RGBManager::showError()
{
    Logger::info("[RGB] ERROR");

    for (int i = 0; i < 3; i++)
    {
        pixels.setPixelColor(
            0,
            pixels.Color(255,0,0)
        );

        pixels.show();

        delay(150);

        pixels.clear();

        pixels.show();

        delay(150);
    }
}

void RGBManager::showAlert()
{
    Logger::info("[RGB] ALERT");

    pixels.setPixelColor(
        0,
        pixels.Color(255,0,0)
    );

    pixels.show();
}