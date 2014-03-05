/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/
/*
Uav.cpp - Clase para gestión de la unidad autónoma de vuelo.
*/
#include <Arduino.h>
#include "Uav.h"

Uav::Uav(void)
{
  _numMotores = N_MOTORES;
}

void Uav::start ()
{
  
  for (int i=0; i<_numMotores; i++){
    M[i].init(V_ESTABLE);
    
  }
  
}

int Uav::getNumMotores(){
  return _numMotores;
}

