#include "Sensors/ENS160AHT21.h"

Adafruit_AHTX0 aht;
ScioSense_ENS160 ens160(ENS160_I2CADDR_1);
//ScioSense_ENS160 ens160(ENS160_I2CADDR_0);

//?Cambiar a dht160aht21Humidity o algo asi, para saber de donde proviene cada dato. aniadir variables a los otro sensores

int Humidity;
int TempC;
int Tvoc;
int Eco2;
int Aqi;

void ENS160AHT21_Setup() {
  Serial.println("------------------------------------------------------------");
  Serial.println("ENS160 + AHT");
  Serial.println();
  Serial.println();
  
  delay(1000);
  Serial.print("ENS160...");
  ens160.begin();
  Serial.println(ens160.available() ? "done." : "failed!");
  if (ens160.available()) {
    Serial.print("\tRev: "); Serial.print(ens160.getMajorRev());
    Serial.print("."); Serial.print(ens160.getMinorRev());
    Serial.print("."); Serial.println(ens160.getBuild());
    Serial.print("\tStandard mode ");
    Serial.println(ens160.setMode(ENS160_OPMODE_STD) ? "done." : "failed!");
  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
     }
    Serial.println("AHT21 found");
  }
  Serial.println("------------------------------------------------------------");
}

void ENS160AHT21_Get() {
  sensors_event_t humidity1, temp;
  aht.getEvent(&humidity1, &temp);
  TempC = (temp.temperature);
  Humidity = (humidity1.relative_humidity);
  if (ens160.available()) {
    ens160.set_envdata(TempC, Humidity);
    ens160.measure(true);
    ens160.measureRaw(true);

    Aqi = ens160.getAQI();
    Tvoc = ens160.getTVOC();
    Eco2 = ens160.geteCO2();
  }
  yield();
  Serial.print("Temp: "); Serial.print(TempC); Serial.println("°C\t");
  Serial.print("Humidity: "); Serial.println(Humidity); 
  Serial.print("AQI: ");Serial.print(Aqi);Serial.println("\t");
  Serial.print("TVOC: ");Serial.print(Tvoc);Serial.println("ppb\t"); 
  Serial.print("CO2: ");Serial.print(Eco2);Serial.println("ppm\t");
}