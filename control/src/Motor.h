/*
Motor.h - Clase para la gestión de motores.
Creada por Roberto Finistrosa, 20 Febrero 2014.
Released into the public domain.
*/

#ifndef _MOTOR_H
#define _MOTOR_H 1

#include <Arduino.h>

class Motor
{
  public:
    Motor(void);
    void init(unsigned long v0);
    void setVelocidad(unsigned long v);
    unsigned long getVelocidad(void);
  
  private:
    unsigned long _velocidad;
};

#endif


