#include "Communications/LORA.h"
#include "Sensors/DHT22.h"
#include "Sensors/ENS160AHT21.h"
#include "Sensors/INA219.h"
#include "Sensors/TSL2561.h"

#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif

SX1262 lora = new Module(NSS, DIO1, RST, BUSY);

// Transmission state variables
volatile bool transmitted_flag = false;  // Flag to indicate if transmission is complete
int transmission_state = RADIOLIB_ERR_NONE;  // Variable to store transmission state

// Interrupt function triggered when transmission is complete
#if defined(ESP8266) || defined(ESP32)
ICACHE_RAM_ATTR
#endif

void set_transmitted_flag() {
    transmitted_flag = true;  // Set the flag to true when transmission is done
}


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
   for(int N = 0; N < 5; N++){
    digitalWrite(PINLED, HIGH);
    delay(250);
    digitalWrite(PINLED,LOW);
    delay(250);
  }
  // Inicializa el módulo LoRa con una frecuencia de 868 MHz
  int state = lora.begin(frequency, bitrate, power, spreadFactor, syncWord, bandwidth, codingRate);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Error al inicializar LoRa, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state);
    while (true); // Detén el programa si falla la inicialización
  }
  attachInterrupt(digitalPinToInterrupt(DIO1), set_transmitted_flag, RISING);
  lora.setPacketSentAction(set_transmitted_flag);

  // Configura el Sync Word para asegurar comunicación entre dispositivos
  //lora.setSyncWord(syncWord);
  Serial.println("LoRa inicializado correctamente.");
  Serial.print("Device: ");
  Serial.println(LoRa_Device);
  Serial.print("MAC: "); 
  Serial.println(LoRa_MAC);
  digitalWrite(PINLED, LOW);
  lora.finishTransmit();
  delay(1000);
}

void get_all_data(JsonDocument& doc){
  // Agrega los datos de los sensores al objeto JSON
  doc["D"] = LoRa_Device;
  doc["M"] = LoRa_MAC;

  // Agregar el primer sensor (DHT22)

  doc["1"]["T1"] = DHT22_Temp;
  doc["1"]["H1"] = DHT22_Hum;

  // Agregar el segundo sensor (ENS160AHT21)
  doc["2"]["T2"] = TempC;
  doc["2"]["H2"] = Humidity;
  doc["2"]["Tvoc"] = Tvoc;
  doc["2"]["Eco2"] = Eco2;

  // Agregar el tercer sensor (INA219)
  doc["3"]["I"] = current_mA;
  doc["3"]["V"] = busVoltage;
  doc["3"]["P"] = power_mW;
  doc["3"]["SV"] = shuntVoltage;

  // Agregar el cuarto sensor (TSL2561)
  doc["4"]["L"] = TSL2561_Lux;
  // ? si da problemas al enviar, llamar otra vez a la funcion LORA_Send para enviar 2 veces.
}

  // Envia el paquete
void LORA_Send(JsonDocument& doc){
  String jsonString;
  serializeJson(doc, jsonString);  // Convert JSON document to a string

  // Measure the JSON size in bytes
  size_t jsonSize = measureJson(doc);
  Serial.print("JSON message size in bytes: ");
  Serial.println(jsonSize);

  // Turn LED on before starting transmission
  Serial.println("---------------------------------------");
  Serial.println("---------------------------------------");
  Serial.print("Paquete: ");
  Serial.println(counter);

  transmission_state = lora.startTransmit(jsonString.c_str());   
    if (transmission_state == RADIOLIB_ERR_NONE) {
        Serial.print("Message ");
        Serial.print(counter);
        Serial.println(" is being transmitted...");
        Serial.println("---------------------------------------");
        Serial.println("Message: ");
        Serial.println(jsonString);
        Serial.println("---------------------------------------");
    } else {
        // Turn LED off if transmission fails
        digitalWrite(PINLED, HIGH);
        Serial.print("Error starting transmission, code: ");
        Serial.println(transmission_state);
    }

  // Check the transmission status
    check_transmission_status();
    counter++;
}

  void check_transmission_status() {
    unsigned long previousMillis = 0;  // Almacena el tiempo del último cambio de LED
    const long interval = 250;         // Intervalo de parpadeo en milisegundos
    int ledState = LOW;                // Estado actual del LED
    int blinkCount = 0;                // Contador de parpadeos
    Serial.println("Checking transmission status...");
    //Serial.print("FLAG before reset: ");
    //Serial.println(transmitted_flag);
    delay (2000); //!cambiar de nuevo a 2500 si problemas, como la mama de nickolasflowers

    if (transmitted_flag) {  // If transmission is complete
        transmitted_flag = false;  // Reset the flag

        if (transmission_state == RADIOLIB_ERR_NONE) {
          Serial.println("Message sent successfully.");
          
          blinkCount = 0;  // Reiniciar el contador
          unsigned long startMillis = millis();  // Guardar el tiempo de inicio
          previousMillis = startMillis;
  
          while (blinkCount < 4) {  // 4 cambios (ON-OFF-ON-OFF) = 2 parpadeos
              unsigned long currentMillis = millis();
              if (currentMillis - previousMillis >= interval) {
                  previousMillis = currentMillis;
                  ledState = !ledState;  // Alternar estado del LED
                  digitalWrite(PINLED, ledState);
                  blinkCount++;
              }
          }
        } else {
            Serial.print("Transmission failed, code: ");
            Serial.println(transmission_state);
        }
        // Clean up after transmission
        lora.finishTransmit();
        // Visual indication using LED (blinks 3 times)
    }
    else { 
      Serial.println("LoRa busy...");	
    }
  digitalWrite(PINLED, LOW); // Apaga el LED
  Serial.println("---------------------------------------");
}
