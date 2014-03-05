/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/
/*
Motor.cpp - Clase para gestión de motores.
*/
#include <Arduino.h>
#include "Motor.h"

Motor::Motor(void)
{
  
}

void Motor::init (unsigned long v0)
{
  _velocidad = v0;
}
void Motor::setVelocidad(unsigned long v)
{
  _velocidad = v;
} 

unsigned long Motor::getVelocidad(void)
{
  return _velocidad;
} 

 
