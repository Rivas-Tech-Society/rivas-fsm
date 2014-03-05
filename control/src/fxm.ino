/* Copyright (C) 2014 RIVAS TECH SOCIETY. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 RIVAS TECH SOCIETY y @Diverduino
 Web      :  http://www.diverduino.com
 e-mail   :  diverduino@gmail.com
*/

/*
Proyecto: Cuadricoptero - FXM - RIVAS TECH SOCIETY
Unidad autónoma de vuelo, con las siguientes características:

- Motores A2208-12T 1500KV motor sin escobillas Outrunner
- Control de velocidad (ESC) Skywalker 20A Brushless Motor Electronic Speed Controller
- IMU GY-85 6DOF 9DOF
- Controlador PID para estabilidad (cabeceo, alabeo y guiñada, y altura)
- Angulos de EULER
- 

*/

#include <PID_v1.h>

//usamos la librería Timer para generar eventos de tiempo
#include "Timer.h"
Timer t1, t2;

// fichero con la configuración básica del sistema
#include "Parametros.h"

// UAV
#include "Uav.h"
Uav uav;

// IMU
#include "Imu.h"
Imu imu;

//SERVO
#include <Servo.h>  // servo library

//Las variables volatile se emplean en la interrupción 
volatile int estado = HIGH ;
volatile int contador = 0 ;
volatile unsigned long time;

int v[N_MOTORES];
// En el caso del balancín, voy a usar un servo sólo, que nos dará el ajuste de velocidad para dos motores
// Calculo el offset, y lo que le sumo a uno se lo resto a otro
// Si esto no va fino añadiremos otro servo

// En el caso del balancín sólo usaremos 2: sE y sO
Servo sN, sS, sE, sO;

// Pines analógicos donde conectamos el acelerómetro
// Para el balancín sólo usaremos el X
const int Xpin = A0;  
const int Ypin = A1;                  
const int Zpin = A2;                  

// 
const int gX = A3;
const int gY = A4;
const int gZ = A5;
double zeroValue[6] = { 0 }; // gyroX, gyroY, gyroZ, accX, accY, accZ

//Usamos un controlador PID para el ROLL, en el caso del balancín es suficiente
// para el cuadricoptero usaremos otro para el PITCH, otro para el YAW y otro para la ALTURA
//Variables para el controlador PID
double rollSetpoint, rollInput, rollOutput;

//Definimos valores agresivos  (para acercarnos más rápidamente al objetivo) y conservadores
// El ajuste de estos parámetros es la parte más complicada de este proyecto. De momento usaremos sólo P
double aggKp=0.5, aggKi=0, aggKd=0;
double consKp=0.01, consKi=0, consKd=0;
//Creamos el PID
PID rollPID(&rollInput, &rollOutput, &rollSetpoint,consKp,consKi,consKd, DIRECT);


void setup(){
  // Conexión del acelerómetro ADXL335 a la placa Arduino. Cambiar cuando llegue la IMU
  // Conectamos un cable del pin AREF a 3.3V
  analogReference(EXTERNAL);  // La tensión aplicada en el pin AREF será la que haga que el conversor A/D 
                              // de su máxima lectura (1023)

  Serial.begin(9600);


  delay(100);//wait for the sensor to get ready

  // Para calibrar la imu. Ejecutar sólo las primeras veces
  
  for (uint8_t i = 0; i < 100; i++) { // Take the average of 100 readings
    zeroValue[0] += analogRead(gX);
    zeroValue[1] += analogRead(gY);
    zeroValue[2] += analogRead(gZ);
    zeroValue[3] += analogRead(Xpin);
    zeroValue[4] += analogRead(Ypin);
    zeroValue[5] += analogRead(Zpin);
    delay(10);
  }
  zeroValue[0] /= 100;
  zeroValue[1] /= 100;
  zeroValue[2] /= 100;
  zeroValue[3] /= 100;
  zeroValue[4] /= 100;
  zeroValue[5] /= 100;
  zeroValue[5] -= 102.3; // Z value is -1g when facing upwards - Sensitivity = 0.33/3.3*1023=102.3
 
  imu.setAccXZeroG(zeroValue[3]);  // aprox 512
  //imu.setAccYZeroG(zeroValue[4]);
  //imu.setAccZZeroG(zeroValue[5]);
  
    // utilizada para generar eventos de tiempo cada dos segundos
  //int tickEvent1 = t1.every(5000, actualizaVelocidad, (void*)0);
  int tickEvent2 = t2.every(500, muestraEstado, (void*)0);

  // No es necesario, porque por defecto son de entrada, pero....
  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  pinMode(Zpin, INPUT);
  
  // Hacemos las primeras lecturas de la IMU
  // Para el uso del balancin con los dos motores, sólo vamos a necesitar un controlador PID sobre el eje X del acelerómetro. Es decir sólo vamos a controlar el alabeo (ROLL) 
  imu.setAccX(analogRead(Xpin)); // Leemos el valor de la tensión en el pin x
  imu.setAccY(analogRead(Ypin)); // Leemos el valor de la tensión en el pin x
  imu.setAccZ(analogRead(Zpin)); // Leemos el valor de la tensión en el pin x
  rollInput = imu.getAccX();
  //rollSetpoint = imu.getAccXZeroG(); 
  rollSetpoint = ACC_X_REPOSO;
  //turn the PID on
  rollPID.SetMode(AUTOMATIC);
  rollPID.SetOutputLimits(-1000, 1000);
 
  // Arrancamos el Quad
  uav.start();
  // Conectamos el servo al Pin 9D
  switch (N_MOTORES) {
    case 2:
      //balancín
        sE.attach(9);  // servo control Motor Dcho
        sO.attach(10);  // servo control Motor Izqdo
        // Para elevarnos, samos una velocidad
        sE.write(V_ARRANQUE);
        sO.write(V_ARRANQUE);
      break;
    case 4:
      //cuadricoptero
        sN.attach(7);  // servo control Motor Arriba
        sS.attach(8);  // servo control Motor Abajo
        sE.attach(9);  // servo control Motor Dcho
        sO.attach(10);  // servo control Motor Izqdo
      break;
  }
  
  // Cuando tengamos los motores, conectaremos la velocidad de los mismos con la del servo
  // De momento solo activamos el servo
  
  //Esperamos 3 segundos para despegar
  delay(3000);
  
  //Reducimos a la velocidad que consideramos estable
  sE.write(V_ESTABLE);
  sO.write(V_ESTABLE);
}


void loop(){
    // llamada a la generación de eventos de tiempo
  //t1.update();
  t2.update();
  
  //Lectura datos IMU
  imu.setAccX(analogRead(Xpin)); // Leemos el valor de la tensión en el pin X
  imu.setAccY(analogRead(Ypin)); // Leemos el valor de la tensión en el pin Y
  imu.setAccZ(analogRead(Zpin)); // Leemos el valor de la tensión en el pin Z
  rollInput = imu.getAccX();
  
  // Aplicación controlador PID
  
  double gap = abs(rollSetpoint-rollInput); //distance away from setpoint
  if(gap<10)
  {  //we're close to setpoint, use conservative tuning parameters
    rollPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     rollPID.SetTunings(aggKp, aggKi, aggKd);
  }

  rollPID.Compute();
  
  
  // Actualización Velocidad Motores
  
  actualizaVelocidadRoll(rollOutput);
  
  
  Serial.print("Input: ");
  Serial.print(rollInput);
  Serial.print(" Salida: ");
  Serial.print(rollOutput);
  Serial.print(" Setpoint: ");
  Serial.print(rollSetpoint);

  Serial.print(" Roll: ");
  Serial.print(imu.getRoll());
  Serial.print(" Pitch: ");
  Serial.println(imu.getPitch());


}


 void actualizaVelocidadRoll(float offset)
 {
   
      uav.M[0].setVelocidad(V_ESTABLE+offset);
      uav.M[1].setVelocidad(V_ESTABLE-offset);
      sE.write(uav.M[0].getVelocidad());
      sO.write(uav.M[1].getVelocidad());
 }
   


   

 
 void muestraEstado(void *context)
 {

     // Revisamos el estado de la IMU
      Serial.print("AccX: ");
      Serial.print(imu.getAccX());
      Serial.print("\t");
      Serial.print("AccXZeroG: ");
      Serial.print(imu.getAccXZeroG());
      Serial.print("\t");
      
   // Revisamos el estado de la UAV
      Serial.print("Numero Motores: ");
      Serial.print(uav.getNumMotores());
      Serial.print("\t");
      
      for (int i = 0; i< N_MOTORES; i++){
          Serial.print("Motor ");
          Serial.print(i);
          Serial.print(": ");
          Serial.print(uav.M[i].getVelocidad());
          Serial.print("\t");
     }
       Serial.print("\n");
  
 }

