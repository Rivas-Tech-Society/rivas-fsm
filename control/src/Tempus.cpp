/*
Tempus.cpp - Librería para gestión de tiempo.
Creada por Roberto Finistrosa, 10 Noviembre 2013.
Released into the public domain.
*/
#include <Arduino.h>
#include "Tempus.h"

Tempus::Tempus(void)
{
  
}

void Tempus::init (unsigned long t0)
{
  _tempus0 = t0;
}

unsigned long Tempus::segundos(unsigned long ms)
{
  return ms/1000;
} 

unsigned long Tempus::minutos(unsigned long ms)
{
  return ms/1000/60;
} 

unsigned long Tempus::dif(unsigned long ms)
{
  return ms - _tempus0;
} 
