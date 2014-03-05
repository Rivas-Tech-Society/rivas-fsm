/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/
/*
Motor.h - Clase para la gestión de motores.
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


