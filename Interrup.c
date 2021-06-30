#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_pit.h"
#include "Interrup.h"

#define DEMO_PIT_BASEADDR PIT /*PIT(Macro) = ((PIT_Type *)PIT_BASE)
                               *PIT_BASE(Macro) = 0x40037000u (Absolute Address) -> 'PIT Module Control Register(PIT_MCR)'(Modo debug)
                               *PIT_Type(Estructura): Contiene la dirección absoluta de memoria de los registros del PIT
                                Tales como: LDVALn(Load Value:periodo)/ CVALn(Current Value:posición actual)/
                                TCTRLn(Timer Control: habilitar timer)/ TFLGn(Timer Flag: configuración de bandera 1/0)
                               */
#define DEMO_PIT_CHANNEL  kPIT_Chnl_0
#define PIT_LED_HANDLER   PIT0_IRQHandler
#define PIT_IRQ_ID        PIT0_IRQn
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)



void PORTx_IRQ()
{
	//Inicialización de interrupciones por GPIO
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTC_IRQn);

	//Nivel de prioridad (la prioridad más baja es 16)
    NVIC_SetPriority(PORTA_IRQn, 2);
    NVIC_SetPriority(PORTC_IRQn, 1);


}

void PIT1_act(uint32_t frec_nom)
{
	 /* Structure of initialize PIT */
	    pit_config_t pitConfig; //Variable boleana: true: Timers run in debug mode; false: Timers stop in debug mode

	    /* Board pin, clock, debug console init */
	    BOARD_BootClockRUN(); //Configuración del Reloj

	    /*
	     * pitConfig.enableRunInDebug = false;
	     */
	    //Configuración por default config->enableRunInDebug = false.
	    PIT_GetDefaultConfig(&pitConfig); // Los Timers se detienen en modo debug

	    /* Init pit module */
	    PIT_Init(DEMO_PIT_BASEADDR, &pitConfig); //Se habilita el reloj del timer(PIT_MCR) y controla el timer en modo debug
	                                             // Se habilita el control del timer (PIT_TCTRLn),

	    /* Set timer period for channel 0 */
	    //Controla el periodo de la frecuencia de la señal, cargando el valor con el registro LDVAL
	    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, USEC_TO_COUNT(frec_nom, PIT_SOURCE_CLOCK));

	    /* Enable timer interrupts for channel 0 */
	    /*Habilita la bandera por medio del registro TCTRLN(bit 1:TIE) en el arreglo de la estructura CHANNEL[4]
	    base->CHANNEL[channel].TCTRL |= mask; */
	    PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);

	    /* Enable at the NVIC */
	    EnableIRQ(PIT_IRQ_ID);

	    /* Start channel 0 */
	    /* Se da inicio al conteo del timer en el canal canal 0(DEMO_PIT_CHANNEL -> kPIT_Chnl_0: 0U ), con ayuda del registro
	       TCTRL, como miembro de la estructura CHANNEL[4], poniendo uno el bit TIE, ya que el TFLG está configurado.
	     * base->CHANNEL[channel].TCTRL |= PIT_TCTRL_TEN_MASK;
	     */
	    PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL); //Comienza el conteo con el timer en el canal 0
}
