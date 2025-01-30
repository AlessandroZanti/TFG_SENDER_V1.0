#ifndef TSL2561
#define TSL2561

#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// Crear un objeto para el sensor TSL2561
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345); // Dirección por defecto (0x39)

void TSL2561_Setup();
void TSL2561_Get();

#endif
