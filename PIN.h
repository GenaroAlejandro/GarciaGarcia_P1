#ifndef PIN_H_
#define PIN_H_
#include <stdio.h>
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pit.h"

#define PIN22      22u
#define PIN26      26u
#define PIN21      21u
#define PIN11      11u
#define PIN10      10u
#define PIN06       6u
#define PIN04       4u
#define PIN03       3u
#define PIN02       2u
#define PIN01       1u
#define PIN00       0u
#define DEMO_PIT_BASEADDR PIT /*PIT(Macro) = ((PIT_Type *)PIT_BASE)
                               *PIT_BASE(Macro) = 0x40037000u (Absolute Address) -> 'PIT Module Control Register(PIT_MCR)'(Modo debug)
                               *PIT_Type(Estructura): Contiene la dirección absoluta de memoria de los registros del PIT
                                Tales como: LDVALn(Load Value:periodo)/ CVALn(Current Value:posición actual)/
                                TCTRLn(Timer Control: habilitar timer)/ TFLGn(Timer Flag: configuración de bandera 1/0)
                               */
#define DEMO_PIT_CHANNEL  kPIT_Chnl_0
#define PIT1   PIT0_IRQHandler
#define PIT_IRQ_ID        PIT0_IRQn
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

void inic_pines();
void PinB_out1();
void PinB_out0();
void PinD_read();
void PIN_inB();




#endif /* PIN_H_ */

#define DEMO_PIT_BASEADDR PIT /*PIT(Macro) = ((PIT_Type *)PIT_BASE)
                               *PIT_BASE(Macro) = 0x40037000u (Absolute Address) -> 'PIT Module Control Register(PIT_MCR)'(Modo debug)
                               *PIT_Type(Estructura): Contiene la dirección absoluta de memoria de los registros del PIT
                                Tales como: LDVALn(Load Value:periodo)/ CVALn(Current Value:posición actual)/
                                TCTRLn(Timer Control: habilitar timer)/ TFLGn(Timer Flag: configuración de bandera 1/0)
                               */
