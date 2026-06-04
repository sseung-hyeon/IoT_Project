#include <Arduino.h>
#include "StateMachine.h"

StateMachine lockerFSM;

void setup() 
{
    Serial.begin(115200);

    lockerFSM.begin();
}

void loop() 
{
    lockerFSM.update();

    delay(1000);
}
