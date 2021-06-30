#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_dac.h"
#include "fsl_common.h"}
#include "DAC.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DAC_BASE DAC0 /* DAC0(Macro)= ((DAC_Type *)DAC0_BASE)
                                * DAC0_BASE(Macro)=  (0x400CC000u)
                                * DAC_Type(Estructura)= contiene todos los registros del DAC
                                  tales como: DATL(Data Low Register "DACx_DATnL")/
                                  DATH(Data High Register "DACx_DATnH")/
                                  SR(Status Register "DACx_SR")/ C0(Control Register "DACx_C0")/
                                  C1(Control Register 1 "DACx_C1")\ C2(Control Register 2 "DAC_C2")
                               */

/*******************************************************************************
 * Variables
 ******************************************************************************/
dac_config_t dacConfigStruct;

void inic_DAC()
{
	/* Configure the DAC. */
	    /*
	     * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
	     * dacConfigStruct.enableLowPowerMode = false;
	     */
	    DAC_GetDefaultConfig(&dacConfigStruct); /*Configuración del bit DACRFS ->1 (En el registro DACx_C0)
	                                              utiliza el voltaje de referencia 1/
	                                             *Configuración del bit LPEN -> 0 (En el registro DACx_C0)
	                                              no utiliza el modo de bajo consumo*/
	    DAC_Init(DAC_BASE, &dacConfigStruct); /*Configuración de reloj para el inicio del DAC
	                                                     CLOCK_EnableClock(s_dacClocks[DAC_GetInstance(base)]);
	                                                    *Configuración del Control Register DACx_C0 con mascara
	                                                     tmp8 = base->C0 & (uint8_t)(~(DAC_C0_DACRFS_MASK | DAC_C0_LPEN_MASK)); base=DAC_Type
	                                                     donde puede ser que: tmp8 |= DAC_C0_DACRFS_MASK;
	                                                     o que:               tmp8 |= DAC_C0_LPEN_MASK;
	                                                     finalmente se configura:base->C0 = tmp8; base=DAC_Type
	                                                   */
	    DAC_Enable(DAC_BASE, true);             /* Enable output (Habilitación de la salida).
	                                                        habilitado:base->C0 |= (uint8_t)DAC_C0_DACEN_MASK; base=DAC_Type
	                                                        deshabilit:base->C0 &= (uint8_t)(~DAC_C0_DACEN_MASK); base=DAC_Type
	                                                     */

	    DAC_SetBufferReadPointer(DAC_BASE, 0U); /* Make sure the read pointer to the start. */
	                                                     /*
	                                                      * The buffer is not enabled, so the read pointer can not move automatically. However, the buffer's read pointer
	                                                      * and itemss can be written manually by user.
	                                                        canfigura el Control Register 2: bits-> 3210(DACBFUP): Límite superior
	                                                        del Búfer del DAC. El puntero de selección del búfer no puede ser excedido
	                                                      */
	    PRINTF("\r\n DAC iniciado !");
}

void DAC_SetValue(uint16_t dacValue)
{
	DAC_SetBufferValue(DAC_BASE, 0U, dacValue);
}
