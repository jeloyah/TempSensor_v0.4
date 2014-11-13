/* ###################################################################
**     Filename    : main.c
**     Project     : Sensor_Temperatura
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-09-09, 14:28, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "AdcLdd1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "WAIT1.h"
#include "Bit1.h"
#include "BitIoLdd1.h"
#include "Bit2.h"
#include "BitIoLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*	Temp(uint16 *Pdata,uint *Ptemp)
 * 	Convierte un valor del ADC a a temperatura, solo para el sensor LM-t85
 * 	*Pdata apuntador con la dirección de los datos entrantes, buffer ADC.
 * 	*Ptr apuntador con la dirección de los datos de salida.
 *
 * */

void	Temp(uint16	*Pdata, uint8	*Ptr)
{
	uint32	temp;
	char buff[4];
	temp=(*Pdata*2970)/65535;
	temp=1926000-(1228*temp);
	temp=temp/100;
	sprintf(buff,"%i",temp);
	memcpy(Ptr,&buff,sizeof(buff));
}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
		uint16	Size_Rx, Sent, ADC0_Value, ADC_Channel;
		uint8	temp, err,UART_Rx,i;
		uint8	*P;
		struct {					//	Esta estructura guarda los datos que se enviaran a traves de UART0
			char	Header[4];		//	Header de datos.
			uint32	SecuenceN;		//	Numero de la secuencia de datos.
			uint8	SensorT;		//	Tipo de sensor
			uint8	SensorN;        //  Numero de sensor
			uint8	SensorS;        //  Estado del sensor
			uint8	ReportT;        //  Tipo de reporte
			uint8	DataL;          //  Longitud de los datos
			char	Value[4];		//	Valor de la variable

		}Data;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  Data.Header[0]='A';			// Se insertaron valores de prueba para la trama de datos
  Data.Header[1]='5';
  Data.Header[2]='D';
  Data.Header[3]='F';
  Data.SecuenceN=0x01;
  Data.SensorT=0x54;
  Data.SensorN=0x01;
  Data.SensorS=0xFF;
  Data.ReportT="A";
  Data.DataL=0x04;
  
  for(;;) {
  	  do{									//Este ciclo espera un dato a traves del UART
  	  	  err = AS1_RecvChar(&UART_Rx);		//Recive un dato de tipo char o uint8 o byte a traves del UART
  	  }while(err != ERR_OK);
  	  do{
  	  switch (UART_Rx)
  	  {
  	  case 0x01:
  		  Bit1_PutVal(TRUE);
  		  Bit2_PutVal(TRUE);
		  for(;;){

			  AD1_Measure(TRUE);				//Enciende la captura del ADC.
			  AD1_GetValue(&ADC0_Value);		//Obtiene el valor capturado por el ADC
			//AD1_Measure(FALSE);				//Detiene la captura del ADC

			  Temp(&ADC0_Value,&Data.Value);

			  AS1_SendBlock(&Data,17, &Sent);	//Envia un bloque e datos a traves del UART0
			  err = AS1_RecvChar(&UART_Rx);
			  if(UART_Rx == 0x02){break;}
			  WAIT1_Waitms(2000);									//Pausa en la ejecucion (el tiempo no es muy preciso)

		  }
		  break;
  	  case 0x02:
  		  Bit1_PutVal(FALSE);
  		  Bit2_PutVal(FALSE);
  		  AD1_Measure(FALSE);
  		  break;
  	  default:
  		  break;
  	  }
  	  }while(0);


  }
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
