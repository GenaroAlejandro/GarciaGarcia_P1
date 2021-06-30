/*
 * Interrupcione.h
 *
 *  Created on: 24 jun. 2021
 *      Author: aleja
 */

#ifndef INTERRUP_H_
#define INTERRUP_H_
#include <stdio.h>
/*
#define frecuen1 1000000U
#define frecuen2 2000000U
#define frecuen3 3000000U
#define frecuen4 4000000U
#define frecuen5 5000000U
*/
void PORTx_IRQ();
void PIT1_act(uint32_t frec_nom);
void PIT1_des();


#endif /* INTERRUP_H_ */
