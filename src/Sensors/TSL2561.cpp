#include "Sensors/TSL2561.h"

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345); // Dirección por defecto (0x39)

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
  // Crear un objeto para almacenar los datos del sensor
  sensors_event_t event;
  tsl.getEvent(&event);

  // Verificar si se obtuvieron lecturas válidas
  if (event.light) {
    Serial.print("Luz detectada: ");
    Serial.print(event.light);
    Serial.println(" lux");
  } else {
    Serial.println("No se detectó luz (el sensor puede estar saturado o apagado).");
  }

  delay(1000); // Leer cada segundo
}
