/**************************************************************************************/
/* 								Author   : Mark Ehab                                  */
/* 								Date     : Mar 4, 2022                                */
/* 								Module	 : STK                                        */
/* 								Version  : V 1.0                                      */
/**************************************************************************************/

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_

/**********************************************************************************************************/
/*									Important Notes	on SYSTICK									    	  */
/*																								 	  	  */
/* Note(1)	: The number of ticks (RELOAD) value can be any value in the range 0x00000001-0x00FFFFFF 	  */
/*																								     	  */
/* Note(2)	: The RELOAD value is calculated according to its use:										  */
/*			  1) To generate a multi-shot timer with a period of N processor clock cycles, use a RELOAD   */
/*  		  value of N-1. For example, if the SysTick interrupt is required every 100 clock pulses, set */
/* 	    	  RELOAD to 99.                                                                               */
/* 	          2) To deliver a single SysTick interrupt after a delay of N processor clock cycles, use a   */
/*  		  RELOAD of value N. For example, if a SysTick interrupt is required after 400 clock		  */
/*  		  pulses, set RELOAD to 400.																  */
/*																								 	  	  */
/**********************************************************************************************************/

								/* Function Prototypes */
void STK_STKInit();
void STK_SetBusyWait(uint32_t Copy_Ticks);
void STK_SetIntervalSingle(uint32_t Copy_Ticks , void (*Copy_Ptr)(void));
void STK_SetIntervalPeriodic(uint32_t Copy_u32Ticks , void (*Copy_Ptr)(void));
void STK_StopTimer(void);
uint32_t STK_GetElapsedTime(void);
uint32_t STK_GetRemainingTime(void);

#endif /* STK_INTERFACE_H_ */
