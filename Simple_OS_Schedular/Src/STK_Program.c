/**************************************************************************************/
/* 								Author   : Mark Ehab                                  */
/* 								Date     : Mar 4, 2022                                */
/* 								Module	 : STK                                        */
/* 								Version  : V 1.0                                      */
/**************************************************************************************/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_Config.h"
#include "STK_Interface.h"
#include "STK_Private.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                            GLOBAL VARIABLES DEFINITIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
void(*Callback_Func)(void);
uint8_t Global_u8IntervalMode;

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*
 * 1- Selects the Clock Source from Configuration File
 * 2- Disables SYSTICK Timer
 * 3- Disables SYSTICK Interrupt
 */
void STK_STKInit()
{
	/* Disable SYSTICK Timer and SYSTICK Interrupt */
	STK_CTRL = 0x00000000;
	#if   STK_CLK_SRC == STK_AHB_DIV_EIGHT
	/* Select AHB/8 as Clock Source of SYSTICK Timer */
	CLEAR_BIT(STK_CTRL,2);
	#elif STK_CLK_SRC == STK_AHB
	/* Select AHB as Clock Source of SYSTICK Timer */
	SET_BIT(STK_CTRL,2);
	#else
		#error " Wrong Clock Source Configuration "
	#endif
}
/*Delays or Locks the Processor for N Clock Cycles Based on the Number of Ticks Passed (Synchronous)*/
void STK_SetBusyWait(uint32_t Copy_Ticks)
{
	if(Copy_Ticks >= 0x00000001 && Copy_Ticks <= 0x00FFFFFF)
	{
		/* Set the Number of ticks (Reload or Start) Value in STK_LOAD Register */
		STK_LOAD = Copy_Ticks;
		/* Start (Enable) SYSTICK Timer */
		SET_BIT(STK_CTRL,0);
		/* Lock the processor until SYSTICK timer reaches 0 */
		while (GET_BIT(STK_CTRL,16) != 1){};
		/* Stop (Disable) SYSTICK Timer */
		CLEAR_BIT(STK_CTRL, 0);
		/* Clear SYSTICK Timer and Flag */
		STK_LOAD = 0;
		STK_VAL = 0;
	}
	else
	{
		/* Return Error */
	}
}
/*Sets A Count-Down Timer that Generates An Interrupt When it Reaches 0 After N Clock Cycles Based on the Number of Ticks Passed (Asynchronous)*/
void STK_SetIntervalSingle(uint32_t Copy_Ticks , void (*Copy_Ptr)(void))
{
	if(Copy_Ticks >= 0x00000001 && Copy_Ticks <= 0x00FFFFFF)
	{
		/* Assign the passed function as a callback function to be called in ISR when triggered */
		Callback_Func = Copy_Ptr;
		/* Set the interval mode */
		Global_u8IntervalMode = STK_INTERVAL_SINGLE;
		/* Set the Number of ticks (Reload or Start) Value in STK_LOAD Register */
		STK_LOAD = Copy_Ticks;
		/* Enable SYSTICK Interrupt */
		SET_BIT(STK_CTRL,1);
		/* Start (Enable) SYSTICK Timer */
		SET_BIT(STK_CTRL,0);
	}
	else
	{
		/* Return Error */
	}
}
/*Sets A Count-Down Timer that Generates An Interrupt When it Reaches 0 Every N Clock Cycles Based on the Number of Ticks Passed (Asynchronous)*/
void STK_SetIntervalPeriodic(uint32_t Copy_Ticks , void (*Copy_Ptr)(void))
{
	if(Copy_Ticks >= 0x00000001 && Copy_Ticks <= 0x00FFFFFF)
	{
		/* Assign the passed function as a callback function to be called in ISR when triggered */
		Callback_Func = Copy_Ptr;
		/* Set the interval mode */
		Global_u8IntervalMode = STK_INTERVAL_PERIODIC;
		/* Set the Number of ticks (Reload or Start) Value in STK_LOAD Register */
		STK_LOAD = Copy_Ticks;
		/* Enable SYSTICK Interrupt */
		SET_BIT(STK_CTRL,1);
		/* Start (Enable) SYSTICK Timer */
		SET_BIT(STK_CTRL,0);
	}
	else
	{
		/* Return Error */
	}
}
/*Stops the SYSTICK Timer*/
void STK_StopTimer(void)
{
	/* Disable SYSTICK Interrupt */
	CLEAR_BIT(STK_CTRL,1);
	/* Stop (Disable) SYSTICK Timer */
	CLEAR_BIT(STK_CTRL,0);
	/* Clear SYSTICK Timer and Flag */
	STK_LOAD = 0;
	STK_VAL = 0;
}
/*Calculates The Elapsed Time of SYSTICK Timer*/
uint32_t STK_u32GetElapsedTime(void)
{
	uint32_t Local_u32ElapsedTime;
	Local_u32ElapsedTime = STK_LOAD - STK_VAL;
	return Local_u32ElapsedTime;
}
/*Calculates The Remaining Time of SYSTICK Timer*/
uint32_t STK_u32GetRemainingTime(void)
{
	uint32_t Local_u32RemainingTime;
	Local_u32RemainingTime = STK_VAL;
	return Local_u32RemainingTime;
}
/*SYSTICK Exception Handler*/
void SysTick_Handler(void)
{
	if(Global_u8IntervalMode == STK_INTERVAL_SINGLE)
	{
		/* Disable SYSTICK Interrupt */
		CLEAR_BIT(STK_CTRL,1);
		/* Stop (Disable) SYSTICK Timer */
		CLEAR_BIT(STK_CTRL,0);
		/* Clear SYSTICK Timer */
		STK_LOAD = 0;
	}
		/* Clear SYSTICK Flag */
		STK_VAL = 0;
		Callback_Func();

}
