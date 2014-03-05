/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/
/*
Tempus.cpp - Librería para gestión de tiempo.
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
