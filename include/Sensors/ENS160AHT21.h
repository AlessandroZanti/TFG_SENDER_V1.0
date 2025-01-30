#ifndef ENS160AHT21_H
#define ENS160AHT21_H

#include <ScioSense_ENS160.h>
#include <Adafruit_AHTX0.h>

extern Adafruit_AHTX0 aht;

//ScioSense_ENS160 ens160(ENS160_I2CADDR_0);

//?Cambiar a dht160aht21Humidity o algo asi, para saber de donde proviene cada dato. aniadir variables a los otro sensores

extern int Humidity;
extern int TempC;
extern int Tvoc;
extern int Eco2;
extern int Aqi;

void ENS160AHT21_Setup();
void ENS160AHT21_Get();

#endif
