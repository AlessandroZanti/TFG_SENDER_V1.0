#include "Sensors/TSL2561.h"

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345); // Dirección por defecto (0x39)

float TSL2561_Lux;

void TSL2561_Setup() {
  // Inicializar la comunicación serial
  Serial.println("Iniciando TSL2561...");

  // Inicializar el TSL2561
  if (!tsl.begin()) {
    Serial.println("No se encontró el sensor TSL2561. Verifica la conexión.");
    while (1);
  }
  Serial.println("TSL2561 inicializado correctamente.");

  // Configuración del sensor
  tsl.enableAutoRange(true); // Habilitar el ajuste automático de rango
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); // Tiempo de integración (más rápido, menos precisión)

  Serial.println("Configuración completada.");
}

void TSL2561_Get() {

  sensors_event_t event;
  tsl.getEvent(&event);

  if (event.light) {
    TSL2561_Lux = event.light;  // Guardar la lectura en la variable global
  } else {
    TSL2561_Lux = -1;  // Usamos -1 para indicar error o sensor saturado
  }
}

void TSL2561_Print(){
  Serial.println("---------------------------------------");
  Serial.println("                TSL2561                ");
  if (TSL2561_Lux >= 0) {
    Serial.print("Luz detectada: ");
    Serial.print(TSL2561_Lux);
    Serial.println(" lux");
  } else {
    Serial.println("No se detectó luz (el sensor puede estar saturado o apagado).");
  }
  Serial.println("---------------------------------------");
}