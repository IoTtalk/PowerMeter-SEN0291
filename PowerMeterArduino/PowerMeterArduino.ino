#include <Wire.h>
#include "DFRobot_INA219.h"
#include <Bridge.h>

DFRobot_INA219_IIC     ina219(&Wire, INA219_I2C_ADDRESS4);
float ina219Reading_mA = 1000;
float extMeterReading_mA = 1000;

void setup() {
    while(ina219.begin() != true) {
        Serial.println("INA219 begin faild");
        delay(2000);
    }
    ina219.linearCalibrate(ina219Reading_mA, extMeterReading_mA);

    pinMode(13,OUTPUT);
    Bridge.begin();   // Pins 0 and 1 should be avoided as they are used by the Bridge library.
    Serial.begin(115200);
}

void loop() {
    char  pin13[2];
    char  valueStr[21];
    float value;

    Bridge.get("Reg_done",  pin13, 2);
    digitalWrite(13, atoi(pin13));    

    value = ina219.getBusVoltage_V();
    dtostrf(value, 2, 2, valueStr);
    Bridge.put("Volt-I", valueStr);
    Serial.print("Volt: ");
    Serial.print(valueStr);
    Serial.println(" V");

    value = ina219.getCurrent_mA();

    dtostrf(value, 4, 2, valueStr);
    Bridge.put("Current-I", valueStr);
    Serial.print("Current: ");
    Serial.print(valueStr);
    Serial.println(" mA");

    value = ina219.getPower_mW();
    dtostrf(value, 6, 2, valueStr);
    Bridge.put("Power-I", valueStr);    
    Serial.print("Power: ");
    Serial.print(valueStr);
    Serial.println(" mW");

    Serial.println();

    delay(5000);
}
