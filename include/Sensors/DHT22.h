#ifndef DHT22_H
#define DHT22_H

#include <Adafruit_Sensor.h>
#include <DHT.h>

// Definir el pin y el tipo de sensor
#define SDHT22 20      // GPIO donde está conectado el DHT22
#define DHTTYPE DHT22 // Tipo de sensor (DHT11, DHT21, DHT22)

void DHT22_Setup(DHT &dht);
void DHT22_Get();

#endif
