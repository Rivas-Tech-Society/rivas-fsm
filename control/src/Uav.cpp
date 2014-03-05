/*
Uav.cpp - Clase para gestión de la unidad autónoma de vuelo.
Creada por Roberto Finistrosa, 20 Febrero 2014.
Released into the public domain.
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
    M[i].init(V_ARRANQUE);
    
  }
  
}

int Uav::getNumMotores(){
  return _numMotores;
}

