#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_pit.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#include "RGB.h"
#include "PIN.h"
//Estructura de configuraciones para el PIN a utilizar
const port_pin_config_t port_pin_config2 = {
	      kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	     kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	     kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	     kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	     kPORT_HighDriveStrength,                                 /* High drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };
const port_pin_config_t port_pin_config_in2 = {
	     kPORT_PullDown,                                            /* Internal pull-up resistor is enabled */
	     kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	     kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	     kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	     kPORT_HighDriveStrength,                                 /* High drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };

gpio_pin_config_t pit_config_out2= {
        kGPIO_DigitalOutput,
        1,
    };
gpio_pin_config_t pit_config_out02= {
        kGPIO_DigitalInput,
        0,
    };
gpio_pin_config_t pit_config_in2= {
		kGPIO_DigitalInput,
        0,
    };
gpio_pin_config_t sw_config2 = {
        kGPIO_DigitalInput,
        0,
    };
uint8_t Cx=0;
uint8_t Lx=0;
uint8_t dato[Long_Dato];
uint8_t valor=0;
uint8_t contador=0;
volatile bool barrer = false;
//ISR PORT D PINES
void PORTD_IRQHandler(void)
{
    GPIO_PortClearInterruptFlags(GPIOD, 1U << PIN00);
    GPIO_PortClearInterruptFlags(GPIOD, 1U << PIN02);
    GPIO_PortClearInterruptFlags(GPIOD, 1U << PIN03);
    GPIO_PortClearInterruptFlags(GPIOD, 1U << PIN01);
	//Limpieza del valor de la interrupción en el registro SFR
    PRINTF("\r\n Interrupcion barrido !");
	PRINTF("\r\n read int 00: %d !",GPIO_PinRead (GPIOD,PIN00));
	PRINTF("\r\n read int 02: %d !",GPIO_PinRead (GPIOD,PIN02));
	PRINTF("\r\n read int 03: %d !",GPIO_PinRead (GPIOD,PIN03));
	PRINTF("\r\n read int 01: %d !",GPIO_PinRead (GPIOD,PIN01));
    if(GPIO_PinRead (GPIOD,PIN00))
    {

        set_color(rgb, LED_clear);
       	set_color(verde, LED_act);

    	Cx=1;
    }
    if(GPIO_PinRead (GPIOD,PIN02))
    {


        set_color(rgb, LED_clear);
        set_color(blanco, LED_act);

     	Cx=2;
    }
    if(GPIO_PinRead (GPIOD,PIN03))
    {


        set_color(rgb, LED_clear);
        set_color(morado, LED_act);

     	Cx=3;
    }
    if(GPIO_PinRead (GPIOD,PIN01))
    {

        set_color(rgb, LED_clear);
        set_color(rojo, LED_act);

     	Cx=4;
    }
    PRINTF("\r\n Cx: %d !",Cx);

    /***************************************/
	PinB_out0();


	PORT_SetPinConfig(PORTB, PIN02, &port_pin_config2); // PIN L1
	GPIO_PinInit(GPIOB, PIN02, &pit_config_out2);  //Inicia PIN L1 ->DDR input
	if((GPIO_PinRead (GPIOD,PIN00))||(GPIO_PinRead (GPIOD,PIN02))||(GPIO_PinRead (GPIOD,PIN03))||(GPIO_PinRead (GPIOD,PIN01)))
	{
		Lx=1;
	}

	PORT_SetPinConfig(PORTB, PIN02, &port_pin_config_in2);
	GPIO_PinInit(GPIOB, PIN02, &pit_config_out02);  //Inicia PIN L1 ->DDR input
	PRINTF("\r\n Lx: %d !",Lx);


	PORT_SetPinConfig(PORTB, PIN03, &port_pin_config2); // PIN L2
	GPIO_PinInit(GPIOB, PIN03, &pit_config_out2);  //Inicia PIN L2 ->DDR input
	if((GPIO_PinRead (GPIOD,PIN00))||(GPIO_PinRead (GPIOD,PIN02))||(GPIO_PinRead (GPIOD,PIN03))||(GPIO_PinRead (GPIOD,PIN01)))
	{
		Lx=2;
	}
	PORT_SetPinConfig(PORTB, PIN03, &port_pin_config_in2);
	GPIO_PinInit(GPIOB, PIN03, &pit_config_out02);  //Inicia PIN L2 ->DDR input


	PORT_SetPinConfig(PORTB, PIN10, &port_pin_config2); // PIN L3
	GPIO_PinInit(GPIOB, PIN10, &pit_config_out2);  //Inicia PIN L3 ->DDR input
	if((GPIO_PinRead (GPIOD,PIN00))||(GPIO_PinRead (GPIOD,PIN02))||(GPIO_PinRead (GPIOD,PIN03))||(GPIO_PinRead (GPIOD,PIN01)))
	{
		Lx=3;
	}


	PORT_SetPinConfig(PORTB, PIN10, &port_pin_config_in2);
	GPIO_PinInit(GPIOB, PIN10, &pit_config_out02);  //Inicia PIN L3 ->DDR input

	PORT_SetPinConfig(PORTB, PIN11, &port_pin_config2); // PIN L4
	GPIO_PinInit(GPIOB, PIN11, &pit_config_out2);  //Inicia PIN L4 ->DDR input
	if((GPIO_PinRead (GPIOD,PIN00))||(GPIO_PinRead (GPIOD,PIN02))||(GPIO_PinRead (GPIOD,PIN03))||(GPIO_PinRead (GPIOD,PIN01)))
	{
		Lx=4;
	}
	PORT_SetPinConfig(PORTB, PIN11, &port_pin_config_in2);
	GPIO_PinInit(GPIOB, PIN11, &pit_config_out02);  //Inicia PIN L4 ->DDR input
	PRINTF("\r\n Lx: %d !",Lx);
	/***************************************/
    //Macrofunción para habilitar un sistema de sincronización Periférico-Core
    SDK_ISR_EXIT_BARRIER;
}


void set_color (uint8_t color, uint8_t estado_col)
{
	if (estado_col==LED_act)
	{
		switch(color)
		{
		  case rojo:  GPIO_PortClear(GPIOB, 1u << PIN22);
			  break;
		  case azul:  GPIO_PortClear(GPIOB, 1u << PIN21);
			  break;
		  case verde: GPIO_PortClear(GPIOE, 1u << PIN26);
			  break;
		  case morado:  GPIO_PortClear(GPIOB, 1u << PIN22);
			            GPIO_PortClear(GPIOB, 1u << PIN21);
			  break;
		  case amarillo: GPIO_PortClear(GPIOB, 1u << PIN22);
			             GPIO_PortClear(GPIOE, 1u << PIN26);
			  break;
		  case blanco:   GPIO_PortClear(GPIOB, 1u << PIN22);
	    	             GPIO_PortClear(GPIOB, 1u << PIN21);
	    	             GPIO_PortClear(GPIOE, 1u << PIN26);
			  break;
		  default:
		  			  break;

		}
	}
	else if(estado_col==LED_des)
	{
		switch(color)
		{
		  case rojo:  GPIO_PortSet(GPIOB, 1u << PIN22);

			  break;
		  case azul:  GPIO_PortSet(GPIOB, 1u << PIN21);
			  break;
		  case verde: GPIO_PortSet(GPIOE, 1u << PIN26);
			  break;
		  case morado:  GPIO_PortSet(GPIOB, 1u << PIN22);
			            GPIO_PortSet(GPIOB, 1u << PIN21);
			  break;
		  case amarillo: GPIO_PortSet(GPIOB, 1u << PIN22);
			             GPIO_PortSet(GPIOE, 1u << PIN26);
			  break;
		  case blanco:   GPIO_PortSet(GPIOB, 1u << PIN22);
	    	             GPIO_PortSet(GPIOB, 1u << PIN21);
	    	             GPIO_PortSet(GPIOE, 1u << PIN26);
			  break;
		  default:
			  break;

		}

	}

	else
	{
		GPIO_PortSet(GPIOB, 1u << PIN22);
		GPIO_PortSet(GPIOB, 1u << PIN21);
		GPIO_PortSet(GPIOE, 1u << PIN26);

	}

}

float in_matriz()
{
	float cantidad=0.0;
	float valorfin=0.0;
	while(contador!=Long_Dato)
	{
		while(Cx==0)
		{
		NVIC_EnableIRQ(PORTD_IRQn);
		NVIC_SetPriority(PORTC_IRQn, 3);
		PRINTF("\r\n read 00: %d !",GPIO_PinRead (GPIOD,PIN00));
		PRINTF("\r\n read 02: %d !",GPIO_PinRead (GPIOD,PIN02));
		PRINTF("\r\n read 03: %d !",GPIO_PinRead (GPIOD,PIN03));
		PRINTF("\r\n read 01: %d !",GPIO_PinRead (GPIOD,PIN01));
		PinB_out1();
		set_color(rgb, LED_clear);
		set_color(azul, LED_act);
		}
		DisableIRQ(PORTD_IRQn);
	    captura();
	    PRINTF("\r\n contador: %d !",contador);

	}
	contador=0;
	if((dato[unidades]==10)||(dato[unidades]==11)||(dato[unidades]==12)||(dato[unidades]==13)||(dato[unidades]==15))
	{
		switch(dato[unidades])
		{
		case 10: return frec1;
		  break;
		 case 11: return frec2;
		  break;
		 case 12: return frec3;
		  break;
		 case 13: return frec4;
		  break;
		 case 15: return frec5;
		  break;
		}
	}


	else
	{
		PRINTF("dat[]: %d\r\n",dato[unidades]);
		cantidad=(float) dato[unidades];
		PRINTF("unidades: %f\r\n", cantidad);
		valorfin+=cantidad;

		PRINTF("dat[]: %d\r\n",dato[decimas]);
		cantidad=(float)dato[decimas];
		cantidad/=10;
		valorfin+=cantidad;
		PRINTF("decimas: %f\r\n", cantidad);

	}



	return valorfin;
}


/*
void barrido()
{
	set_color(rgb, LED_clear);
    set_color(amarillo, LED_act);
	PinD_out0();
	GPIO_PortSet (GPIOB, 1u<<PIN02);
	if(!GPIO_PinRead (GPIOD,PIN00))
	{
		Cx=1;
	}
	GPIO_PortSet (GPIOB, 0u<<PIN02);

	GPIO_PortSet (GPIOB, 1u<<PIN03);
	if(!GPIO_PinRead (GPIOD,PIN02))
	{
		Cx=2;
	}
	GPIO_PortSet (GPIOB, 0u<<PIN03);

	GPIO_PortSet (GPIOB, 1u<<PIN10);
	if(!GPIO_PinRead (GPIOD,PIN03))
	{
		Cx=3;
	}
	GPIO_PortSet (GPIOB, 0u<<PIN10);

	GPIO_PortSet (GPIOB, 1u<<PIN11);
	if(!GPIO_PinRead (GPIOD,PIN01))
	{
		Cx=4;
	}
	GPIO_PortSet (GPIOB, 0u<<PIN11);
	PRINTF("\r\n Cx: %d !",Cx);
	captura();
}*/


void captura()
{
	switch(Cx)
	{
	  case Columna1: if(Lx==1){ dato[contador]=1; contador++; } //vol
	               if(Lx==2){ dato[contador]=4; contador++; } //vol
	               if(Lx==3){ dato[contador]=7; contador++; } //vol
	               if(Lx==4){ dato[contador]=15; contador++; } //punto
		  break;

	  case Columna2: if(Lx==1){ dato[contador]=2; contador++; } //vol
	               if(Lx==2){ dato[contador]=5; contador++; } //vol
	               if(Lx==3){ dato[contador]=8; contador++; } //vol
	               if(Lx==4){ dato[contador]=0; contador++; } //vol
		  break;

	  case Columna3: if(Lx==1){ dato[contador]=3; contador++; } //vol
	               if(Lx==2){ dato[contador]=6; contador++; }//vol
	               if(Lx==3){ dato[contador]=9; contador++; }//vol
	               if(Lx==4){ dato[contador]=14; contador++; }//asterisco
		  break;

	  case Columna4: if(Lx==1){ dato[contador]=10; contador++; }//frec
	               if(Lx==2){ dato[contador]=11; contador++; }//vol
	               if(Lx==3){ dato[contador]=12; contador++; }//no val
	               if(Lx==4){ dato[contador]=13; contador++; }//fre
		  break;
	}
	PRINTF("\r\n contador: %d !",contador);
	Cx=0;
	Lx=0;
}
