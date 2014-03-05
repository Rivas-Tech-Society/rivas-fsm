/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/
/*
Tempus.h - Librería para gestión de tiempo.
*/

#ifndef _TEMPUS_H
#define _TEMPUS_H 1

#include <Arduino.h>

class Tempus
{
  public:
    Tempus(void);
    void init(unsigned long t0);
    unsigned long segundos(unsigned long ms);
    unsigned long minutos(unsigned long ms);
    unsigned long dif(unsigned long ms);
  
  private:
    unsigned long _tempus0;
};

#endif




