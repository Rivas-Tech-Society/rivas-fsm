/*
Motor.cpp - Clase para gestión de motores.
Creada por Roberto Finistrosa, 20 Febrero 2014.
Released into the public domain.
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

 
