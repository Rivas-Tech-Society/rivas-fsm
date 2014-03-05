/*
Proyecto: Cuadricoptero - FXM - RIVAS TECH SOCIETY
Fichero de parámetros

Autor: Rivas Tech Society & www.diverduino.com
Licencia: 
*/

#define N_MOTORES 2 // Balancín-Bicoptero

// Rango de velocidades de los motores. Dado que usamos servo, el grado que le demos al servo se traduce en la velocidad de los motores 
// Usaremos el rango 0-180
#define V_REPOSO 0
#define V_MAXIMA 180
#define V_ARRANQUE 90
#define V_ESTABLE 70
#define V_PASO 1  //Incremento - Decremento de velocidad

// Tunning Acelerómetro. Situación en reposo es en el plano horizontal
#define ACC_X_REPOSO 512 // Medida tomada tras varias lecturas
#define ACC_Y_REPOSO 0  // Sin calibrar. No usado en balancín
#define ACC_Z_REPOSO 0   // Sin calibrar. No usado en balancín
#define ACC_MARGEN 10 //Parámetro para ajuste en las lecturas. No usado de momento





