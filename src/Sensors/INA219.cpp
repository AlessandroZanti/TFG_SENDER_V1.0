#include "Sensors/INA219.h"

void INA219_Setup() {
  Serial.println("Inicializando INA219...");

  // Inicializar el bus I2C con pines personalizados
  //Wire.begin(SDA, SCL);

  // Inicializar el INA219
  if (!ina219.begin(&Wire)) { // Pasar el bus I2C personalizado
    Serial.println("Error al inicializar el INA219. Verifica la conexión.");
    while (1); // Detener si falla la inicialización
  }

  Serial.println("INA219 inicializado correctamente.");
  ina219.setCalibration_32V_2A(); // Configuración de rango máximo (32V, 2A)
}


void INA219_Get() {
  // Leer mediciones del INA219
  float busVoltage = ina219.getBusVoltage_V();       // Voltaje del panel solar
  float shuntVoltage = ina219.getShuntVoltage_mV();  // Caída de voltaje en el shunt
  float current_mA = ina219.getCurrent_mA();         // Corriente hacia la carga
  float power_mW = ina219.getPower_mW();             // Potencia generada

  // Mostrar resultados en el monitor serie
  Serial.print("Voltaje del panel solar: "); Serial.print(busVoltage); Serial.println(" V");
  Serial.print("Caída de voltaje en el shunt: "); Serial.print(shuntVoltage); Serial.println(" mV");
  Serial.print("Corriente hacia la carga: "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Potencia generada: "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("---------------------------------------");

  delay(1000); // Leer datos cada segundo
}
