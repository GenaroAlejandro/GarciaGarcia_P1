#include <stdio.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#include "PIN.h"



gpio_pin_config_t pit_config_out= {
        kGPIO_DigitalOutput,
        1,
    };
gpio_pin_config_t pit_config_out0= {
        kGPIO_DigitalInput,
        0,
    };
gpio_pin_config_t pit_config_in= {
		kGPIO_DigitalInput,
        0,
    };
gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };
//Estructura de configuraciones para el PIN a utilizar
const port_pin_config_t port_pin_config = {
	      kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	     kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	     kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	     kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	     kPORT_HighDriveStrength,                                 /* High drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };
const port_pin_config_t port_pin_config_in = {
	     kPORT_PullDown,                                            /* Internal pull-up resistor is enabled */
	     kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	     kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	     kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	     kPORT_HighDriveStrength,                                 /* High drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };

void inic_pines()
{

	//Función de la API para habilitar el reloj del multiplexor
	//kCLOCK_Portx: Macro con el valor en el registro SCGC5 del PORTA, PORTB, PORTC, PORTD y PORTE
	 CLOCK_EnableClock(kCLOCK_PortA);
	 CLOCK_EnableClock(kCLOCK_PortB);
	 CLOCK_EnableClock(kCLOCK_PortC);
	 CLOCK_EnableClock(kCLOCK_PortE);
	 CLOCK_EnableClock(kCLOCK_PortD);

     //Configuración del PIN: Puerto/PIN/Estructura de configuración para...
	PORT_SetPinConfig(PORTA, PIN04, &port_pin_config); // sw3
	PORT_SetPinConfig(PORTC, PIN06, &port_pin_config); // sw2
	PORT_SetPinConfig(PORTE, PIN26, &port_pin_config); // LED verde
    PORT_SetPinConfig(PORTB, PIN22, &port_pin_config); // LED rojo
	PORT_SetPinConfig(PORTB, PIN21, &port_pin_config); // LED azúl

	PORT_SetPinConfig(PORTB, PIN02, &port_pin_config); // PIN L1
	PORT_SetPinConfig(PORTB, PIN03, &port_pin_config); // PIN L2
	PORT_SetPinConfig(PORTB, PIN10, &port_pin_config); // PIN L3
	PORT_SetPinConfig(PORTB, PIN11, &port_pin_config); // PIN L4

	PORT_SetPinConfig(PORTD, PIN00, &port_pin_config_in); // PIN C1
	PORT_SetPinConfig(PORTD, PIN02, &port_pin_config_in); // PIN C2
	PORT_SetPinConfig(PORTD, PIN03, &port_pin_config_in); // PIN C3
	PORT_SetPinConfig(PORTD, PIN01, &port_pin_config_in); // PIN C4

	//Selección del tipo de interrupción para el PIN (en este caso un flanco de bajada)
	PORT_SetPinInterruptConfig(PORTA, PIN04, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTC, PIN06, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(PORTD, PIN00, kPORT_InterruptLogicOne);
	PORT_SetPinInterruptConfig(PORTD, PIN02, kPORT_InterruptLogicOne);
	PORT_SetPinInterruptConfig(PORTD, PIN03, kPORT_InterruptLogicOne);
	PORT_SetPinInterruptConfig(PORTD, PIN01, kPORT_InterruptLogicOne);
    //kPORT_InterruptRisingEdge
	//Configuración del PIN con el registro del GPIO para seleccionar el comportamiento I/O
	GPIO_PinInit(GPIOA, PIN04, &sw_config); //Inicia sw3 -> DDR input
	GPIO_PinInit(GPIOB, PIN22, &pit_config_out); //Inicia PIN LED rojo -> DDR output
	GPIO_PinInit(GPIOB, PIN21, &pit_config_out); //Inicia PIN LED azúl -> DDR output
	GPIO_PinInit(GPIOB, PIN02, &pit_config_out0);  //Inicia PIN L1 ->DDR output
	GPIO_PinInit(GPIOB, PIN03, &pit_config_out0);  //Inicia PIN L2 ->DDR output
	GPIO_PinInit(GPIOB, PIN10, &pit_config_out0);  //Inicia PIN L3 ->DDR output
	GPIO_PinInit(GPIOB, PIN11, &pit_config_out0);  //Inicia PIN L4 ->DDR output
	GPIO_PinInit(GPIOC, PIN06, &sw_config); //Inicia sw2 -> DDR input
	GPIO_PinInit(GPIOD, PIN00, &pit_config_in);  //Inicia PIN C1 ->DDR input
	GPIO_PinInit(GPIOD, PIN02, &pit_config_in);  //Inicia PIN C2 ->DDR input
	GPIO_PinInit(GPIOD, PIN03, &pit_config_in);  //Inicia PIN C3 ->DDR input
	GPIO_PinInit(GPIOD, PIN01, &pit_config_in);  //Inicia PIN C4 ->DDR input
	GPIO_PinInit(GPIOE, PIN26, &pit_config_out); //Inicia PIN LED azúl -> DDR output


}

void PinB_out1()
{
	PORT_SetPinConfig(PORTB, PIN02, &port_pin_config); // PIN L1
	PORT_SetPinConfig(PORTB, PIN03, &port_pin_config); // PIN L2
	PORT_SetPinConfig(PORTB, PIN10, &port_pin_config); // PIN L3
	PORT_SetPinConfig(PORTB, PIN11, &port_pin_config); // PIN L4

	GPIO_PinInit(GPIOB, PIN02, &pit_config_out);  //Inicia PIN L1 ->DDR input
	GPIO_PinInit(GPIOB, PIN03, &pit_config_out);  //Inicia PIN L2 ->DDR input
	GPIO_PinInit(GPIOB, PIN10, &pit_config_out);  //Inicia PIN L3 ->DDR input
	GPIO_PinInit(GPIOB, PIN11, &pit_config_out);  //Inicia PIN L4 ->DDR input
}

void PinB_out0()
{
	//PRINTF("\r\n se apagaron !");
	PORT_SetPinConfig(PORTB, PIN02, &port_pin_config_in);
	PORT_SetPinConfig(PORTB, PIN03, &port_pin_config_in);
	PORT_SetPinConfig(PORTB, PIN10, &port_pin_config_in);
	PORT_SetPinConfig(PORTB, PIN11, &port_pin_config_in);


	GPIO_PinInit(GPIOB, PIN02, &pit_config_in);  //Inicia PIN L1 ->DDR input
	GPIO_PinInit(GPIOB, PIN03, &pit_config_in);  //Inicia PIN L2 ->DDR input
	GPIO_PinInit(GPIOB, PIN10, &pit_config_in);  //Inicia PIN L3 ->DDR input
	GPIO_PinInit(GPIOB, PIN11, &pit_config_in);  //Inicia PIN L4 ->DDR input
}

/*
void PinD_read()
{
	GPIO_PinRead (GPIOD,PIN00);
	GPIO_PinRead (GPIOD,PIN02);
	GPIO_PinRead (GPIOD,PIN03);
	GPIO_PinRead (GPIOD,PIN01);

}
*/

void PIN_inB()
{
	    PORTD->PCR[PIN00] = 0x00000100; //001 Alternative 1 (GPIO) para el pin 22 en el PORTB
	    PORTD->PCR[PIN02] = 0x00000100;
	    PORTD->PCR[PIN03] = 0x00000100;
	    PORTD->PCR[PIN01] = 0x00000100;


		GPIOB->PDDR = 0x00600000; //PDDR: configuración de salida en el PORTB, pines 22 y 21
		GPIOE->PDDR = 0x04000000; //PDDR: configuración de salida en el PORTB, pine 26
		//GPIOD->PDIR = 0x000000F0;

		PORT_SetPinInterruptConfig(PORTD, PIN00, kPORT_InterruptLogicOne);
		PORT_SetPinInterruptConfig(PORTD, PIN02, kPORT_InterruptLogicOne);
		PORT_SetPinInterruptConfig(PORTD, PIN03, kPORT_InterruptLogicOne);
		PORT_SetPinInterruptConfig(PORTD, PIN01, kPORT_InterruptLogicOne);
}
