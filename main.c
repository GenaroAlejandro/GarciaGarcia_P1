#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "PIN.h"
#include "RGB.h"
#include "Interrup.h"
#include "DAC.h"
#define  frecuencia  0x01u
#define  voltaje  0x02u
#define  base 0x00u
//const uint8_t frecuencia = 1;
//const uint8_t voltaje = 2;
//const uint8_t base = 0;
uint8_t matriz = 0;
volatile bool Estado1 = false;
uint16_t dacVal= 0;
float volt=3.3;
uint16_t conver=0;
uint32_t frec_nom = 1000000U;

/************** ISR ****************/
//ISR PORT A sw3
void PORTA_IRQHandler(void)
{
	//Limpieza del valor de la interrupción en el registro SFR
    GPIO_PortClearInterruptFlags(GPIOA, 1U << PIN04);
    switch(matriz)
    {
        case base: matriz=voltaje;
        break;
        case voltaje: matriz=base;
        break;
    }
    PRINTF("matriz: %d\r\n", matriz);
    //Macrofunción para habilitar un sistema de sincronización Periférico-Core
    SDK_ISR_EXIT_BARRIER;
}

//ISR PORT C sw2
void PORTC_IRQHandler(void)
{
	//Limpieza del valor de la interrupción en el registro SFR
    GPIO_PortClearInterruptFlags(GPIOC, 1U << PIN06);
    switch(matriz)
    {
        case base: matriz=frecuencia;
        break;
        case frecuencia: matriz=base;
        break;
    }

    SDK_ISR_EXIT_BARRIER;
}

//ISR PIT 1
void PIT1(void)
{
	/*pit_chnl_t: variable numerada 0-3
	 * static inline void PIT_ClearStatusFlags(PIT_Type *base, pit_chnl_t channel, uint32_t mask)
      {
          //CHANNEL(arreglo[4]): tipo de dato = PIT_Type
          base->CHANNEL[channel].TFLG = mask; //Selecciona el dato de la estructura, TFGL, y lo iguala a mask =1.
      }
    */
    PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerFlag); //Limpia el registro de la bandera de conversión
    Estado1 = true;
    if(dacVal)
    {
    	dacVal=0;
    }
    else
    {
    	dacVal=conver;
    }

    /* Added for, and affects, all PIT handlers. For CPU clock which is much larger than the IP bus clock,
     * CPU can run out of the interrupt handler before the interrupt flag being cleared, resulting in the
     * CPU's entering the handler again and again. Adding DSB can prevent the issue from happening.
     */
    __DSB();
}

/**********************************/


int main(void) {
	inic_pines();
	//PIN_inB();
	PORTx_IRQ();
	PIT1_act(frec_nom);
	conver=(volt*(4095/3.3));
	inic_DAC();
	while (true)
	{
		if(matriz)
		{
			if(matriz==frecuencia)
			{   float frec=0;
				frec = in_matriz();
				PRINTF("frec_nom: %d\r\n", (uint8_t)frec);
				frec_nom = 1000000*(1/frec);
				PRINTF("frec_nom: %d\r\n", frec_nom);
				while(matriz==frecuencia)
				{
			        set_color(rgb, LED_clear);
			        set_color(amarillo, LED_act);
				}

				PIT1_act(frec_nom);
			}
			if(matriz==voltaje)
			{
				volt = in_matriz();
				//PRINTF("\r\n voltaje= %d !",(uint8_t)volt);
				conver=(uint16_t)(volt*(4095/3.3));
				/*if(conver>4095)
				 * set_color(rgb, LED_clear);
				   set_color(rojo, LED_act);
					while(true)
					{

					}
				}*/
				while(matriz==voltaje)
				{
					set_color(rgb, LED_clear);
					set_color(amarillo, LED_act);
				}
				//matriz=base;
			}





		}
		else
		{
			PRINTF("DAC out: %d\r\n", dacVal);
			DAC_SetValue(dacVal);
			set_color(rgb, LED_clear);
			while(Estado1==false);
			Estado1=false;
			PRINTF("DAC out: %d\r\n", dacVal);
			DAC_SetValue(dacVal);
			set_color(rojo, LED_act);
			while(Estado1==false);
			Estado1=false;

		}
	}


    return 0 ;
}
