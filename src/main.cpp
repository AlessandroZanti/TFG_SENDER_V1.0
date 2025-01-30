#include <Arduino.h>
#include "ALL.h"

void setup() {
    ESP32_Setup();
    DHT22_Setup();
    ENS160AHT21_Setup();
    INA219_Setup();
    TSL2561_Setup();
    
//poner el primero el del esp para evitar errores, donde inicia una unica vez el monitor en serie y el i2c
}

void loop() {
    DHT22_Get();
    ENS160AHT21_Get();
    INA219_Get();
    TSL2561_Get();
}