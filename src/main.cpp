#include <Arduino.h>
#include "StateMachine.h"
#include "config.h"

StateMachine lockerFSM;

void setup() 
{
    Serial.begin(115200);

    delay(1000);
    
    lockerFSM.begin();
}

void loop() 
{
    // FSM 갱신
    lockerFSM.update();

    delay(10);
}
