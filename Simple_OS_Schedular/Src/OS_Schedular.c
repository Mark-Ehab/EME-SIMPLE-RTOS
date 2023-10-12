/****************************************************************/
/* 					Author   	 : Mark Ehab                    */
/* 					Date     	 : Oct 12, 2023               	*/
/*      			SWC          : OS Schedular  			    */
/*     			    Description	 : OS Schedular Program File    */
/* 	   				Version      : V1.0                         */
/****************************************************************/

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                                    LIBRARIES		  		                         */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
#include "STD_TYPES.h"
#include "STD_ERRORS.h"
#include "BIT_MATH.h"

#include "STK_Interface.h"

#include "OS_Schedular.h"

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             GLOBAL VARIABLES DEFINITION		  		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
Task_t Global_TasksArr[NUM_OF_TASKS];


/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*                             FUNCTIONS IMPLEMENTATIONS		  		             */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------*/
/* @Function Name: OS_Init          					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Initializes the OS through setting the system tick and setting */
/*                 up the schedular                                         	  */
/*--------------------------------------------------------------------------------*/
void OS_Init(void)
{
	/* Initialize STK */
	STK_STKInit();

	/* Set the schedular to be called every 1 sec */
	STK_SetIntervalPeriodic(1000000, SCHEDULAR);
}


/*--------------------------------------------------------------------------------*/
/* @Function Name: TASKS_CREATION          					                      */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : uint8_t Copy_Priority                                          */
/* 				   Brief: Priority of the task to be created                      */
/* 				   -------------------------------------------------------------- */
/* 				   uint8_t Copy_Periodicity                                       */
/* 				   Brief: Periodicity of the task to be created (How much time it */
/*                        takes this task to be ready)                            */
/*  			   -------------------------------------------------------------- */
/* 				   void(*Copy_Fptr)(void)                                         */
/* 				   Brief: Pointer to function of the task that will be executed   */
/*                        once the task become ready                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Creates tasks that will be handled by OS						  */
/*--------------------------------------------------------------------------------*/
void TASKS_CREATION(uint8_t Copy_Priority,uint8_t Copy_Periodicity, void(*Copy_Fptr)(void))
{
	/* Assign the passed periodicity to the task based on its passed priority */
	Global_TasksArr[Copy_Priority].TaskPeriodicity = Copy_Periodicity;

	/*
	 *  Register the task function to be called once the task is ready through
	 *  assigning the passed pointer to that function to task based on its passed
	 *  priority
	 */
	Global_TasksArr[Copy_Priority].PointerToFunction = Copy_Fptr;

}

/*--------------------------------------------------------------------------------*/
/* @Function Name: SCHEDULAR          					                          */
/*--------------------------------------------------------------------------------*/
/* @Param(in)	 : None				                                              */
/*--------------------------------------------------------------------------------*/
/* @Param(inout) : None                                                	          */
/*--------------------------------------------------------------------------------*/
/* @Param(out)	 : None                                            	              */
/*--------------------------------------------------------------------------------*/
/* @Return		 : void                                          				  */
/*--------------------------------------------------------------------------------*/
/* @Description	 : Scheduler to manage tasks according to periodicity and         */
/* 				   priority        												  */
/*--------------------------------------------------------------------------------*/
void SCHEDULAR(void)
{
	/* Local Variables Definitions */
	static uint32_t Local_SystemTickCounter = 0; /* A variable to hold system tick counts */
	uint8_t Local_TasksCounter;					 /* A variable to hold task count */

	/* Increment System Tick Counter */
	Local_SystemTickCounter++;

	/*
	 * Traverse over tasks in the system to see which on is ready to be executed
	 * according to periodicity and prority
	 */
	for(Local_TasksCounter = 0 ; Local_TasksCounter < NUM_OF_TASKS ; Local_TasksCounter++)
	{
		/* Check if current task is ready or not */
		if((Local_SystemTickCounter % Global_TasksArr[Local_TasksCounter].TaskPeriodicity) == 0)
		{
			/* Execute the task function */
			Global_TasksArr[Local_TasksCounter].PointerToFunction();
		}
		else
		{
			/* Do Nothing */
		}
	}
}
