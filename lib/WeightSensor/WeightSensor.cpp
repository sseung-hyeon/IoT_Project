#include "WeightSensor.h"
#include "Logger.h"
#include "config.h"

void WeightSensor::begin()
{
    Logger::info("[WEIGHT] Initialized");

    // HX711 시작
    scale.begin(PIN_HX711_DOUT, PIN_HX711_SCK);

    // 임시 보정값, 실제 측정으로 수정 필요
    scale.set_scale(420.0f);

    //영점 설정, 현재 무게를 0으로 설정
    scale.tare();
}

float WeightSensor::getWeightKg()
{
    // HX711 연결 상태 확인
    if (!scale.is_ready())
    {
        Logger::warn(
            "[WEIGHT] HX711 Not Ready"
        );

        return 0.0f;
    }
    
    float weight =
        scale.get_units(5);
        
    Logger::info(
        "[WEIGHT] Weight = " +
        String(weight) +
        " kg"
    );

    return weight;
}

bool WeightSensor::hasPackage()
{
    float weight = getWeightKg();

    return weight > 0.05f;
}