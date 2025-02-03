#ifndef INA219_H
#define INA219_H

//#include <Wire.h>
#include <Adafruit_INA219.h>

extern float busVoltage;
extern float shuntVoltage;
extern float current_mA;
extern float power_mW;

void INA219_Setup();
void INA219_Get();
void INA219_Print();
void INA219_Simu();

#endif
