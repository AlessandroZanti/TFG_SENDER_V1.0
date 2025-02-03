#include "Communications/LORA.h"
#include "Sensors/DHT22.h"
#include "Sensors/ENS160AHT21.h"
#include "Sensors/INA219.h"
#include "Sensors/TSL2561.h"

SX1262 lora = new Module(NSS, DIO1, RST, BUSY);

int counter = 0;

String LoRa_Device = "Panel 1" ;
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
  delay(2000);

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
  delay(1000);
}


void LORA_Send(){
  Serial.println("---------------------------------------");
  Serial.println("---------------------------------------");
  Serial.print("Enviando paquete: ");
  Serial.println(counter);

  /*String message = "hello " + String(counter);
  int state = lora.transmit(message);*/

  String message1 =  String(LoRa_Device)  + String(LoRa_MAC);
  int state1 = lora.transmit(message1);

if (state1 == RADIOLIB_ERR_NONE) {
    Serial.println("Mensaje 1: LoRa enviado con éxito.");
    digitalWrite(PINLED, HIGH); // Enciende el LED
    delay(1000);
    digitalWrite(PINLED, LOW); // Enciende el LED
    delay(1000);
  } else {
    Serial.print("Error al enviar el mensaje 1, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state1);
  }


delay(100);

  String message2 =  String(DHT22_Temp)  + String(DHT22_Hum);
  int state2 = lora.transmit(message2);

if (state2 == RADIOLIB_ERR_NONE) {
    Serial.println("Mensaje 2: DHT22 enviado con éxito.");
    digitalWrite(PINLED, HIGH); // Enciende el LED
    delay(1000);
    digitalWrite(PINLED, LOW); // Enciende el LED
    delay(1000);
  } else {
    Serial.print("Error al enviar el mensaje 2, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state2);
  }

delay(100);

String message3 =  String(current_mA)  + String(busVoltage) + String(power_mW) + String(shuntVoltage);
  int state3 = lora.transmit(message3);

if (state3 == RADIOLIB_ERR_NONE) {
    Serial.println("Mensaje 3: ENS160 + AHT21 enviado con éxito.");
    digitalWrite(PINLED, HIGH); // Enciende el LED
    delay(1000);
    digitalWrite(PINLED, LOW); // Enciende el LED
    delay(1000);
  } else {
    Serial.print("Error al enviar el mensaje 3, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state3);
  }

delay(100);
  
  String message4 =  String(current_mA)  + String(busVoltage) + String(power_mW) + String(shuntVoltage);
  int state4 = lora.transmit(message4);

if (state4 == RADIOLIB_ERR_NONE) {
    Serial.println("Mensaje 4: INA219 enviado con éxito.");
    digitalWrite(PINLED, HIGH); // Enciende el LED
    delay(1000);
    digitalWrite(PINLED, LOW); // Enciende el LED
    delay(1000);
  } else {
    Serial.print("Error al enviar el mensaje 4, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state4);
  }

  delay(100);

  String message5 =  String(TSL2561_Lux);
  int state5 = lora.transmit(message5);

if (state5 == RADIOLIB_ERR_NONE) {
    Serial.println("Mensaje 5: TSL2561 enviado con éxito.");
    digitalWrite(PINLED, HIGH); // Enciende el LED
    delay(1000);
    digitalWrite(PINLED, LOW); // Enciende el LED
    delay(1000);
  } else {
    Serial.print("Error al enviar el mensaje 5, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state5);
  }

delay(100);

  digitalWrite(PINLED, LOW); // Apaga el LED
  counter++;
  Serial.println("---------------------------------------");
}