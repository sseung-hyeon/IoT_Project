#ifndef CONFIG_H
#define CONFIG_H

/*
 * ==========================================================
 * Smart Unmanned Package Locker
 * 전역 설정 파일
 * ==========================================================
 *
 * 규칙
 * 1. 핀 번호는 반드시 여기서만 관리한다.
 * 2. 코드 본문에 숫자 하드코딩 금지.
 * 3. 센서/모터/통신 관련 설정은 모두 이 파일에 정의한다.
 *
 */

// ======================================================
// RFID RC522                       RFID 카드
// ======================================================

#define PIN_RFID_SS      53   
#define PIN_RFID_RST     5 

// SPI (Mega2560 기본 SPI 핀)
// SCK  = 52
// MOSI = 51
// MISO = 50

// ======================================================
// 등록된 RFID 카드 UID
// 실제 카드 태깅 후 값 수정
// ======================================================

#define RFID_UID_0 0xDE
#define RFID_UID_1 0xAD
#define RFID_UID_2 0xBE
#define RFID_UID_3 0xEF

// ======================================================
// Servo Motor (SG90)               서보모터
// ======================================================

#define PIN_SERVO        8              

// 서보 잠금/해제 각도          [임시]
#define SERVO_LOCK_ANGLE      0         // 잠금 위치
#define SERVO_UNLOCK_ANGLE    90        // 잠금 해제 위치 

// ======================================================
// HC-SR04 Ultrasonic Sensor        초음파 센서
// ======================================================

#define PIN_TRIG         6              
#define PIN_ECHO         7

#define PACKAGE_DISTANCE_CM 30      // 내부 택배 존재 판단 거리
// 30cm 이하 택배 있음, 30cm 초과 택배 없음

// ======================================================
// HX711 Load Cell                  로드셀
// ======================================================

#define PIN_HX711_DOUT   3
#define PIN_HX711_SCK    2

#define MAX_WEIGHT_KG    1.2f   // 최대 적재 무게 1.2kg

// ==========================================================
// Shock Sensor (SW-420)            충격센서
// ==========================================================

#define PIN_SHOCK       4      

#define SHOCK_DEBOUNCE_MS 20    // 노이즈 제거용 대기시간

// ==========================================================
// Piezo Buzzer                     피에조 부저
// ==========================================================

#define PIN_BUZZER       9    

// ==========================================================
// WS2812B RGB LED                  LED
// ==========================================================

#define PIN_NEOPIXEL     10         

#define NUM_PIXELS       1          // LED 개수 1개

// ======================================================
// ESP-01 (UART)
// ======================================================

// Mega2560 Serial1 사용
// Mega TX1(D18) -> ESP RX
// Mega RX1(D19) -> ESP TX

#define PIN_ESP_RX       19   
#define PIN_ESP_TX       18   

#define ESP_BAUDRATE 115200

// ==========================================================
// I2C LCD                          LCD
// ==========================================================

// SDA = D20
// SCL = D21

#define LCD_I2C_ADDRESS  0x27

// ==========================================================
// 4x4 Keypad                       키패드
// ==========================================================

// Row Pins
#define PIN_KEYPAD_R1    22
#define PIN_KEYPAD_R2    23
#define PIN_KEYPAD_R3    24
#define PIN_KEYPAD_R4    25

// Column
#define PIN_KEYPAD_C1    26
#define PIN_KEYPAD_C2    27
#define PIN_KEYPAD_C3    28
#define PIN_KEYPAD_C4    29

// ==========================================================
// Security Settings                비밀번호 세팅
// ==========================================================

// 비밀번호 길이
#define PASSWORD_LENGTH      4

// 최대 인증 실패 횟수
#define MAX_AUTH_FAIL_COUNT  5          // 카드/PIN 통합 실패 허용 횟수

// 인증 제한 시간
#define AUTH_TIMEOUT_MS      30000UL    // 30초

// 문 열림 유지 시간
#define DOOR_OPEN_TIMEOUT_MS 10000UL    // 10초

// ==========================================================
// Mock Mode
// ==========================================================

// 하드웨어 조립 전 FSM 테스트용
#define MOCK_AUTO_SUCCESS true

#define MOCK_PACKAGE_DETECTED true
#define MOCK_WEIGHT_KG 0.75f

// ======================================================
// WIFI
// ======================================================

#define WIFI_SSID      "여기에_와이파이이름"
#define WIFI_PASSWORD  "여기에_와이파이비밀번호"

// ======================================================
// FIREBASE
// ======================================================

#define FIREBASE_HOST \
"smartlocker-ba303-default-rtdb.asia-southeast1.firebasedatabase.app"

// 보관함 루트 경로
#define FIREBASE_LOCKER_PATH "/locker"

// 데이터 키
#define FIREBASE_KEY_WEIGHT       "weightKg"
#define FIREBASE_KEY_PACKAGE      "packageDetected"
#define FIREBASE_KEY_ALERT        "alert"
#define FIREBASE_KEY_DOOR         "doorOpen"
#define FIREBASE_KEY_CLEAR_ALERT  "clearAlert"
#define FIREBASE_KEY_LAST_UPDATE  "lastUpdate"
// ======================================================
// Firebase Mock
// ======================================================

// 하드웨어 없이 Firebase 동작 시뮬레이션
#define FIREBASE_MOCK_MODE true



#endif