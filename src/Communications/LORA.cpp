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
  digitalWrite(PINLED, HIGH);
  delay(2000);

  // Inicializa el módulo LoRa con una frecuencia de 868 MHz
  int state = lora.begin(frequency, bitrate, power, spreadFactor, syncWord, bandwidth, codingRate);
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("Error al inicializar LoRa, código: ");
    digitalWrite(PINLED, HIGH);
    Serial.println(state);
    while (true); // Detén el programa si falla la inicialización
  }

  lora.setPacketSentAction(set_transmitted_flag);

  // Configura el Sync Word para asegurar comunicación entre dispositivos
  //lora.setSyncWord(syncWord);
  Serial.println("LoRa inicializado correctamente.");
  digitalWrite(PINLED, LOW);
  lora.finishTransmit();
  delay(1000);
}

void get_all_data(JsonDocument& doc){
  // Agrega los datos de los sensores al objeto JSON
  doc["Device"] = LoRa_Device;
  doc["MAC"] = LoRa_MAC;
   // Crear un array de sensores
  JsonArray sensors = doc.createNestedArray("Sensors");

  // Agregar el primer sensor (DHT22)
  JsonObject dht22 = sensors.createNestedObject();
  dht22["Sensor"] = "DHT22";
  dht22["Temperature"] = DHT22_Temp;
  dht22["Humidity"] = DHT22_Hum;

  // Agregar el segundo sensor (ENS160AHT21)
  JsonObject ens160aht21 = sensors.createNestedObject();
  ens160aht21["Sensor"] = "ENS160AHT21";
  ens160aht21["Temperature"] = TempC;
  ens160aht21["Humidity"] = Humidity;
  ens160aht21["Tvoc"] = Tvoc;
  ens160aht21["Eco2"] = Eco2;

  // Agregar el tercer sensor (INA219)
  JsonObject ina219 = sensors.createNestedObject();
  ina219["Sensor"] = "INA219";
  ina219["Current"] = current_mA;
  ina219["Voltage"] = busVoltage;
  ina219["Power"] = power_mW;
  ina219["ShuntVoltage"] = shuntVoltage;

  // Agregar el cuarto sensor (TSL2561)
  JsonObject tsl2561 = sensors.createNestedObject();
  tsl2561["Sensor"] = "TSL2561";
  tsl2561["Luminosity"] = TSL2561_Lux;

  // Envia el objeto JSON
  LORA_Send(doc);
}
  // Envia el objet
void LORA_Send(JsonDocument& doc){
  String jsonString;
  serializeJson(doc, jsonString);  // Convert JSON document to a string

  // Measure the JSON size in bytes
  size_t jsonSize = measureJson(doc);
  Serial.print("JSON message size in bytes: ");
  Serial.println(jsonSize);
  // Turn LED on before starting transmission
  digitalWrite(PINLED, HIGH);
  delay(1000);
  Serial.println("---------------------------------------");
  Serial.println("---------------------------------------");
  Serial.print("Enviando paquete: ");
  Serial.println(counter);

  transmission_state = lora.startTransmit(jsonString.c_str());   
    if (transmission_state == RADIOLIB_ERR_NONE) {
        Serial.println("Message is being transmitted...");
    } else {
        // Turn LED off if transmission fails
        digitalWrite(PINLED, LOW);
        delay(100);

        Serial.print("Error starting transmission, code: ");
        Serial.println(transmission_state);
    }

  // Check the transmission status
    check_transmission_status();
    counter++;
}

  void check_transmission_status() {
    Serial.println("Checking transmission status...");

    if (transmitted_flag) {  // If transmission is complete
        transmitted_flag = false;  // Reset the flag

        if (transmission_state == RADIOLIB_ERR_NONE) {
            Serial.println("Message sent successfully.");
        } else {
            Serial.print("Transmission failed, code: ");
            Serial.println(transmission_state);
        }

        // Clean up after transmission
        lora.finishTransmit();

        // Visual indication using LED (blinks 3 times)
        for (int i = 0; i < 3; i++) {
            digitalWrite(PINLED, HIGH);
            delay(200);
            digitalWrite(PINLED, LOW);
            delay(200);
        }
    }
  digitalWrite(PINLED, LOW); // Apaga el LED
  Serial.println("---------------------------------------");
  // wait for a second before transmitting again
  delay(100);
}
