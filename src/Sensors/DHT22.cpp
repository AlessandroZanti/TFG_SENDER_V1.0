#include "Sensors/DHT22.h"

DHT dht(SDHT22, DHTTYPE);

void DHT22_Setup(DHT &dht) {
dht.begin(); // Iniciar el sensor
}

void DHT22_Get() {
    float temp = dht.readTemperature(); // Leer temperatura en °C
    float hum = dht.readHumidity();     // Leer humedad en %

    if (!isnan(temp) && !isnan(hum)) {
        Serial.print("Temperatura: ");
        Serial.print(temp);
        Serial.print(" °C  |  Humedad: ");
        Serial.print(hum);
        Serial.println(" %");
    } else {
        Serial.println("Error al leer el sensor");
    }
    
    delay(2000); // Leer cada 2 segundos
}