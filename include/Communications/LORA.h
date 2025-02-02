#ifndef LORA_H
#define LORA_H

#include <RadioLib.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>

// Define los pines del módulo LoRa //! Define los pines del módulo LoRa
#define NSS 8     // Pin NSS (Chip Select)
#define RST 12    // Pin de Reset
#define DIO1 14   // Pin de Interrupción (DIO1)
#define BUSY 13   // Pin Busy (asegúrate de incluirlo si aplica)

// Pines I2C 
#define SDA 19
#define SCL 18

#define PINLED 35 // Pin del LED

#define frequency 900.0 // Frecuencia de operación en MHz
#define syncWord 0xA1 // Sync Word

//TODO Add Funciones de LoRa

void ESP32_Setup();
void LORA_Send(); //? If ralla cambiar sin String y hacerse una raya


#endif


