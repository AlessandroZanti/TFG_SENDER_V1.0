#ifndef TSL2561
#define TSL2561

#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

extern float TSL2561_Lux;

void TSL2561_Setup();
void TSL2561_Get();
void TSL2561_Print();

#endif
