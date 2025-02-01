#include "Communications/LORA.h"

SX1262 lora = new Module(NSS, DIO1, RST, BUSY);

int counter = 0;

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


void LORA_Send(){ //? If ralla cambiar sin String y hacerse una raya
  Serial.println("---------------------------------------");
  Serial.println("---------------------------------------");
  Serial.print("Enviando paquete: ");
  Serial.println(counter);

  // Envía un paquete LoRa
  String message = "hello " + String(counter);
  int state = lora.transmit(message);

  // Verifica el estado del envío
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println("Mensaje enviado con éxito.");
    digitalWrite(PINLED, HIGH); // Enciende el LED
  } else {
    Serial.print("Error al enviar el mensaje, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state);
  }
  delay(500);
    digitalWrite(PINLED, LOW); // Apaga el LED
  counter++;
  Serial.println("---------------------------------------");
  delay(6000); // Espera 10 segundos antes de enviar el siguiente paquete
}