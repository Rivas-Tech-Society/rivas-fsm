/*
Tempus.h - Librería para gestión de tiempo.
Creada por Roberto Finistrosa, 10 Noviembre 2013.
Released into the public domain.
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




