/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/

/*
Imu.cpp - Clase para la gestión de la Unidad de Medida Inercial (IMU).
*/

/*
http://www.instructables.com/id/Guide-to-gyro-and-accelerometer-with-Arduino-inclu/?lang=es
The accelerometer
The accelerometer measures the acceleration (g's) in three dimensions. 
To translate the analog readings into degrees you simply need to read the axis and to subtract the zero offset like so:
accVal = accAdc-accZero

Where accAdc is the analog reading and accZero is the value when it reads 0g - 
this is calculated in the start of the code, look in the "Setup" section. 
The zero value can also be found in the datasheet: http://www.sparkfun.com/datasheets/Components/SMD/adxl335.pdf. You will see that the zero voltage at 0g is approximately 1.5V, to translate this into quids, you again have to use this equation: zeroVoltage/3.3*1023.
So in this example I get:
1.5/3.3*1023=465.

You can then calculate the pitch and roll using the following equations:
pitch = atan2(accYval, accZval)+PI
roll = atan2(accXval, accZval)+PI
*/



#include <Arduino.h>
#include "Imu.h"
#include "Parametros.h"
#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter

Kalman kalmanX;
Kalman kalmanY;



/* All the angles start at 180 degrees */
double gyroXangle = 180;
double gyroYangle = 180;
double gyroZangle = 180;

// Complimentary filter
double compAngleX = 180;
double compAngleY = 180;


Imu::Imu(void)
{
   // Una conversión ADC va de 0 a 1023, siendo 512 
   // la mitad del rango y por lo tanto el 0
   //acc_zero_G = 512.0;
   // Según el Datasheet, tenemos incrementos de 330mV por cada G de aceleración
   // por lo tanto, si pasamos de mV (330) a cuentas (1023)
   // nos queda que 330mV / 1023cuentas = 102.3, valor para convertir mV a G's
   // escala es el número de unidades que esperamos que el sensor lea cuando
   // hay un cambio de aceleración en 1G
  acc_escala = 102.3;


 
}

void Imu::Init(void)
{
  setAccX(ACC_X_REPOSO);
  setAccY(ACC_Y_REPOSO);
  setAccZ(ACC_Z_REPOSO);
  
  kalmanX.setAngle(180); // Set starting angle
  kalmanY.setAngle(180);

 
}

void Imu::setAccX(float x)
{
  acc_x_grav = ((float)x - acc_X_zero_G)/acc_escala;
  acc_x = x;
} 

float Imu::getAccXGrav(void)
{
  return acc_x_grav;
} 

float Imu::getAccX(void)
{
  return acc_x;
} 

void Imu::setAccY(float y)
{
  acc_y_grav = ((float)y - acc_Y_zero_G)/acc_escala;
  acc_y = y;
} 

float Imu::getAccYGrav(void)
{
  return acc_y_grav;
} 

void Imu::setAccZ(float z)
{
  acc_z_grav = ((float)z - acc_Z_zero_G)/acc_escala;
  acc_z = z;
} 

float Imu::getAccZGrav(void)
{
  return acc_z_grav;
} 

void Imu::setAccXZeroG(float x)
{
  acc_X_zero_G = x;
} 

void Imu::setAccYZeroG(float y)
{
  acc_Y_zero_G = y;
} 

void Imu::setAccZZeroG(float z)
{
  acc_Z_zero_G = z;
} 

float Imu::getAccXZeroG(void)
{
  return acc_X_zero_G;
} 

float Imu::getRoll(void)
{
  return (atan2(acc_x - acc_X_zero_G, acc_z - acc_Z_zero_G) + PI) * RAD_TO_DEG;
} 

float Imu::getPitch(void)
{
  return (atan2(acc_y - acc_Y_zero_G, acc_z - acc_Z_zero_G) + PI) * RAD_TO_DEG;
}
