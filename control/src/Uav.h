/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/
/*
Uav.h - Clase para la gestión de la unidad autónoma de vuelo.
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
