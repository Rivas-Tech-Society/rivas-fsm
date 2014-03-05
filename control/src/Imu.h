/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/

/*
Imu.h - Clase para la gestión de la Unidad de Medida Inercial (IMU).
*/

// De momento usamos el Acelerómetro ADXL335, por lo que esta clase sólo se va a usar para la conversión de unidades

#ifndef _IMU_H
#define _IMU_H 1

#include <Arduino.h>

class Imu
{
  public:
    Imu(void);
    void Init();
    void setAccX(float x);
    void setAccY(float y);
    void setAccZ(float z);
    float getAccX(void);
    float getAccXGrav(void);
    float getAccY(void);
    float getAccYGrav(void);
    float getAccZ(void);
    float getAccZGrav(void);
    void setAccXZeroG(float x);
    void setAccYZeroG(float y);
    void setAccZZeroG(float z);
    float getAccXZeroG(void);
    float getRoll();
    float getPitch();
  
  private:
    float acc_x_grav;
    float acc_y_grav;
    float acc_z_grav;
    float acc_x;
    float acc_y;
    float acc_z;
    float acc_x_deg;
    float acc_y_deg;
    float acc_z_deg;
   // Una conversión ADC va de 0 a 1023, siendo 512 
   // la mitad del rango y por lo tanto el 0
   
   //Para calibrar
    float acc_X_zero_G;
    float acc_Y_zero_G;
    float acc_Z_zero_G;
   // Según el Datasheet, tenemos incrementos de 330mV por cada G de aceleración
   // por lo tanto, si pasamos de mV (330) a cuentas (1023)
   // nos queda que 330mV / 1023cuentas = 102.3, valor para convertir mV a G's
   // escala es el número de unidades que esperamos que el sensor lea cuando
   // hay un cambio de aceleración en 1G
    float acc_escala;
};

#endif
