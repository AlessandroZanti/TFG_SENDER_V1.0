#include "Sensors/DHT22.h"

float DHT22_Temp;
float DHT22_Hum;

DHT dht(SDHT22, DHTTYPE);

void DHT22_Setup() {
dht.begin(); // Iniciar el sensor
}

void DHT22_Get() {
    DHT22_Temp = dht.readTemperature(); // Leer temperatura en °C
    DHT22_Hum = dht.readHumidity();     // Leer humedad en %
}

void DHT22_Print(){
    Serial.println("---------------------------------------");
    Serial.println("                 DHT22                 ");
     if (!isnan(DHT22_Temp) && !isnan(DHT22_Hum)) {
        Serial.print("Temperatura: ");
        Serial.print(DHT22_Temp);
        Serial.print(" °C  |  Humedad: ");
        Serial.print(DHT22_Hum);
        Serial.println(" %");
    } else {
        Serial.println("DHT22 ERROR");
    }
}

void DHT22_Simu(){
    DHT22_Temp = 30.5;
    DHT22_Hum = 50.5;
}