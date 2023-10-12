/*===========================================================================*/
/* 					Author   	 : Mark Ehab                                 */
/* 					Date     	 : Oct 12, 2023               	             */
/* 	   				Version      : V1.0                                      */
/*===========================================================================*/
/*                                                                           */
/*    _____ _____ __  __ _____  _      ______   _____ _______ ____   _____   */
/*  / ____|_   _|  \/  |  __ \| |    |  ____| |  __ \__   __/ __ \ / ____|   */
/* | (___   | | | \  / | |__) | |    | |__    | |__) | | | | |  | | (___     */
/*  \___ \  | | | |\/| |  ___/| |    |  __|   |  _  /  | | | |  | |\___ \    */
/*  ____) |_| |_| |  | | |    | |____| |____  | | \ \  | | | |__| |____) |   */
/* |_____/|_____|_|  |_|_|    |______|______| |_|  \_\ |_|  \____/|_____/    */
/*                                                                           */
/*===========================================================================*/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "RCC_Interface.h"
#include "GPIO_Interface.h"

#include "OS_Schedular.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                  TASKS PROTOTYPES		  		                 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
void RED_LED_TASK(void);
void YELLOW_LED_TASK(void);
void GREEN_LED_TASK(void);

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    ENTRY POINT		  		                     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
void main()
{
	/************************System Initializations************************/

	/* Initialize RCC */
	RCC_Init();

	/* Enable system clock for both GPIOA and GPIOC */
	RCC_EnablePeripheralClk(RCC_APB2, RCC_GPIOA);
	RCC_EnablePeripheralClk(RCC_APB2, RCC_GPIOC);

	/* Initialize GPIO pins to which red, yellow and green LEDs are connected */
	GPIO_Init();

	/* Register tasks to OS */
	TASKS_CREATION(0, 1 , RED_LED_TASK);	/* Task1 Registration */
	TASKS_CREATION(1, 2 , YELLOW_LED_TASK);	/* Task2 Registration */
	TASKS_CREATION(2, 5 , GREEN_LED_TASK);	/* Task3 Registration */

	/* Initialize OS */
	OS_Init();

	while(1)
	{

	}
}

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                 TASKS IMPLEMENTATION		  		                 */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
void RED_LED_TASK(void)
{
	/* Toggle Red LED */
	GPIO_TogglePinVal(GPIO_PORT_A, GPIO_PIN_1);
}
void YELLOW_LED_TASK(void)
{
	/* Toggle Yellow LED */
	GPIO_TogglePinVal(GPIO_PORT_C, GPIO_PIN_13);

}
void GREEN_LED_TASK(void)
{
	/* Toggle Green LED */
	GPIO_TogglePinVal(GPIO_PORT_C, GPIO_PIN_15);
}
