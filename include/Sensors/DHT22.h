#ifndef DHT22_H
#define DHT22_H

#include <Adafruit_Sensor.h>
#include <DHT.h>

// Definir el pin y el tipo de sensor
#define SDHT22 20      // GPIO donde está conectado el DHT22
#define DHTTYPE DHT22 // Tipo de sensor (DHT11, DHT21, DHT22)

extern float DHT22_Temp;
extern float DHT22_Hum;

void DHT22_Setup();
void DHT22_Get();
void DHT22_Print();

#endif
