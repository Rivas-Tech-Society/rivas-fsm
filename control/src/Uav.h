/*
Uav.h - Clase para la gestión de la unidad autónoma de vuelo.
Creada por Roberto Finistrosa, 20 Febrero 2014.
Released into the public domain.
*/

#ifndef _UAV_H
#define _UAV_H 1

#include <Arduino.h>

// incluimos el header de parametros porque necesitamos saber el n de motores
#include "Parametros.h"
#include "Motor.h"

class Uav
{
  public:
    Motor M[N_MOTORES];
 
    Uav(void);
    void start();
    int getNumMotores(void);
   
  private:
    int _numMotores;
};

#endif
