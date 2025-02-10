#ifndef LORA_H
#define LORA_H

#include <RadioLib.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <ArduinoJson.h>

// Define los pines del módulo LoRa //! Define los pines del módulo LoRa
#define NSS 8     // Pin NSS (Chip Select)
#define RST 12    // Pin de Reset
#define DIO1 14   // Pin de Interrupción (DIO1)
#define BUSY 13   // Pin Busy (asegúrate de incluirlo si aplica)

// Pines I2C 
#define SDA 19
#define SCL 18

#define PINLED 35 // Pin del LED

//#define frequency 870.0 // Frecuencia de operación en MHz
//#define bitrate 250.0 // Bitrate en kbps
//#define power 12 // Potencia de transmisión en dBm
//#define spreadFactor 8 // Factor de esparcimiento
//#define syncWord 0xA1 // Sync Word
//#define bandwidth 22 // Ancho de banda en kHz
//#define codingRate 12 // Tasa de codificación

#define frequency 870.0 // Frecuencia de operación en MHz
#define bandwidth 500.0 // Ancho de banda en kHz
#define spreadFactor 6 // Factor de esparcimiento
#define codingRate 5
#define syncWord 0xA1 // Sync Word
#define power 12
#define preambleLength 20



extern volatile bool transmitted_flag;  // Flag indicating if transmission is complete
extern int transmission_state;          // Stores the transmission status

//TODO Add Funciones de LoRa

void ESP32_Setup();
void set_transmitted_flag();
void LORA_Send(JsonDocument& doc);
void get_all_data(JsonDocument& doc);
void check_transmission_status();

#endif


