#include "Communications/LORA.h"
#include "Sensors/DHT22.h"
#include "Sensors/ENS160AHT21.h"
#include "Sensors/INA219.h"
#include "Sensors/TSL2561.h"

#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif

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
  lora.finishTransmit();
  delay(1000);
}

void LORA_Send_2(){

  String mensaje = "Hola puto munto"  + String(counter);
  lora.startTransmit(mensaje);
  delay(100);
  Serial.println("---------------------------------------");
  Serial.println("---------------------------------------");
  Serial.print("Enviando paquete: ");
  Serial.println(counter);
   //lora.transmit(mensaje);
    if (lora.startTransmit(mensaje) == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));

    // print measured data rate
    Serial.print(F("[SX1262] Datarate:\t"));
    Serial.print(lora.getDataRate());
    Serial.println(F(" bps"));

  } else if (lora.startTransmit(mensaje) == RADIOLIB_ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 256 bytes
    Serial.println(F("too long!"));

  } else if (lora.startTransmit(mensaje) == RADIOLIB_ERR_TX_TIMEOUT) {
    // timeout occured while transmitting packet
    Serial.println(F("timeout!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(lora.startTransmit(mensaje));
  }

  digitalWrite(PINLED, LOW); // Apaga el LED
  counter++;
  Serial.println("---------------------------------------");
  // wait for a second before transmitting again
  delay(100);
  lora.finishTransmit();
}
