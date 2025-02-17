#include <Arduino.h>
#include "ALL.h"

void setup() {
    ESP32_Setup();
    //DHT22_Setup();
    //ENS160AHT21_Setup();
    //INA219_Setup();
    //TSL2561_Setup();
    
//poner el primero el del esp para evitar errores, donde inicia una unica vez el monitor en serie y el i2c
}

void loop() {
    //DHT22_Get();
    DHT22_Simu();
    //ENS160AHT21_Get();
    ENS160AHT21_Simu();
    //INA219_Get();
    INA219_Simu();
    //TSL2561_Get();
    TSL2561_Simu();
    DHT22_Print();
    ENS160AHT21_Print();
    INA219_Print();
    TSL2561_Print();
    String payload;
    StaticJsonDocument<256> doc;
    get_all_data_String(payload);
    LORA_Send_String(payload);
    //get_all_data_JSON(doc);
    //LORA_Send_JSON(doc);
    delay(1000); //! Cambiar a 2500 si problemas
}