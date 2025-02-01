#ifndef ENS160AHT21_H
#define ENS160AHT21_H

#include <ScioSense_ENS160.h>
#include <Adafruit_AHTX0.h>

//?Cambiar a dht160aht21Humidity o algo asi, para saber de donde proviene cada dato. aniadir variables a los otro sensores

extern float Humidity;
extern float TempC;
extern int Tvoc;
extern int Eco2;
extern int Aqi;

void ENS160AHT21_Setup();
void ENS160AHT21_Get();
void ENS160AHT21_Print();

#endif
