#include "Communications/LORA.h"
#include "Sensors/DHT22.h"
#include "Sensors/ENS160AHT21.h"
#include "Sensors/INA219.h"
#include "Sensors/TSL2561.h"

SX1262 lora = new Module(NSS, DIO1, RST, BUSY);

int counter = 0;

String LoRa_Device = "Panel 1";
String LoRa_MAC = WiFi.macAddress();


void ESP32_Setup(){
// Inicializa el monitor serie
  Serial.begin(115200);

  // Inicializar el bus I2C con pines personalizados
  Wire.begin(SDA, SCL);

  pinMode(PINLED, OUTPUT);
  while (!Serial);
  Serial.println("Inicializando LoRa...");
  digitalWrite(PINLED, HIGH);
  delay(1000);

  // Inicializa el módulo LoRa con una frecuencia de 868 MHz
  int state = lora.begin(frequency);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Error al inicializar LoRa, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state);
    while (true); // Detén el programa si falla la inicialización
  }

  // Configura el Sync Word para asegurar comunicación entre dispositivos
  lora.setSyncWord(syncWord);
  Serial.println("LoRa inicializado correctamente.");
  digitalWrite(PINLED, LOW);
  delay(500);
}


void LORA_Send(){
  Serial.println("---------------------------------------");
  Serial.println("---------------------------------------");
  Serial.print("Enviando paquetes: ");
  Serial.println(counter);

  // Envía el primer paquete LoRa
  String message1 = "Dispositivo:" + String(LoRa_Device) + "   MAC:" + String(LoRa_MAC) + 
                    "   Sensor: DHT22" + "   Temperatura:" + String(DHT22_Temp) + 
                    "   Humedad:" + String(DHT22_Hum) + "   Sensor: ENS160 + AHT21" + 
                    "   Temperatura:" + String(TempC) + "   Humedad:" + String(Humidity) + 
                    "Co2" + String(Eco2) + "TVOC" + String(Tvoc);

  int state1 = lora.transmit(message1);
  delay(100);  // Pequeña pausa entre los dos envíos

  // Envía el segundo paquete LoRa
  String message2 = String("   Sensor: INA219") + "   Corriente:" + String(current_mA) + 
                    "   Voltaje:" + String(busVoltage) + "   Potencia:" + String(power_mW) + 
                    "   ShuntVoltaje:" + String(shuntVoltage) + "   Sensor: TSL2591" + 
                    "   Luz:" + String(TSL2561_Lux);

  int state2 = lora.transmit(message2);

  // Verifica el estado de los envíos
  if (state1 == RADIOLIB_ERR_NONE && state2 == RADIOLIB_ERR_NONE) {
    Serial.println("Ambos mensajes enviados con éxito.");
    digitalWrite(PINLED, HIGH); // Enciende el LED
  } else {
    Serial.print("Error al enviar los mensajes, código de estado: ");
    if (state1 != RADIOLIB_ERR_NONE) {
      Serial.print("state1: ");
      Serial.println(state1);
    }
    if (state2 != RADIOLIB_ERR_NONE) {
      Serial.print("state2: ");
      Serial.println(state2);
    }
    digitalWrite(PINLED, HIGH); // Enciende el LED en caso de error
  }

  digitalWrite(PINLED, LOW); // Apaga el LED
  counter++;
  Serial.println("---------------------------------------");
  delay(6000); // Espera antes de enviar el siguiente paquete
}
