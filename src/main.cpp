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
    //DHT22_Simu();
    ENS160AHT21_Get();
    //ENS160AHT21_Simu();
    INA219_Get();
    //INA219_Simu();
    TSL2561_Get();
    //TSL2561_Simu();
    DHT22_Print();
    ENS160AHT21_Print();
    INA219_Print();
    TSL2561_Print();
    //delay(5000); // Espera antes de enviar el siguiente paquete
    //LORA_Send();
    StaticJsonDocument<256> doc;
    get_all_data(doc);
    LORA_Send(doc);
    delay(2500);
}