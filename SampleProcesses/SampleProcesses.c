/*
 * SampleProcesses.c
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#include "main.h"
#include "../kernel/A_exported_functions.h"
#include "../support/A_printf.h"

void process_1(void)
{
uint8_t		*ptr1;
uint32_t	wakeup;

	create_timer(TIMER_ID_0,200,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			ptr1 = mem_get(512);
			HAL_GPIO_TogglePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin);
			mem_release(ptr1);
		}
	}
}

void process_2(void)
{
uint8_t		*ptr1 = NULL;
uint32_t	wakeup;

	create_timer(TIMER_ID_0,400,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( ptr1 != NULL )
				mem_release(ptr1);
			ptr1 = mem_get(512);
			sprintf((char *) ptr1, "Printf is running\n\r");
			HAL_GPIO_TogglePin(LED2_YELLOW_GPIO_Port, LED2_YELLOW_Pin);
		}
	}
}

void process_3(void)
{
uint8_t		*ptr1 = NULL;
uint32_t	wakeup,msg=0;

	create_timer(TIMER_ID_0,800,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	allocate_hw(DEVICE_USB);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			HAL_GPIO_TogglePin(LED3_RED_GPIO_Port, LED3_RED_Pin);
			if ( ptr1 != NULL )
				mem_release(ptr1);
			ptr1 = mem_get(512);
			sprintf((char *)ptr1, "From process %d message %d\n\r",get_current_process(),msg);
			send_usb(ptr1,strlen((char *)ptr1));
			msg++;
		}
	}
}

void process_4(void)
{
	create_timer(TIMER_ID_0,800,TIMERFLAGS_FOREVER );
	while(1)
	{

	}
}
