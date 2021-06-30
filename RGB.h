/*
 * RGB.h
 *
 *  Created on: 24 jun. 2021
 *      Author: aleja
 */

#ifndef RGB_H_
#define RGB_H_
#include <stdio.h>

#define rojo 0x00u
#define azul 0x01u
#define verde 0x02u
#define morado 0x03u
#define amarillo 0x04u
#define rgb 0x05u
#define blanco 0x05u
#define LED_act 0x01u
#define LED_des 0x02u
#define LED_clear 0x00u
#define Columna1 1u
#define Columna2 2u
#define Columna3 3u
#define Columna4 4u
#define Long_Dato 3u
#define unidades 0u
#define decimas 2u
#define frec1 1.0
#define frec2 2.0
#define frec3 3.0
#define frec4 4.0
#define frec5 5.0




void set_color (uint8_t,uint8_t);
float in_matriz();
void barrido();
void captura();

#endif /* RGB_H_ */
