/*
 * timer.c
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#include "main.h"
#include "A.h"
#include "systems.h"
#include "scheduler.h"
#include "A_exported_functions.h"


extern	PCB_t 		process[MAX_PROCESS];
extern	Asys_t		Asys;

extern	__IO uint32_t uwTick;

void update_global_tick_count(void)
{
	Asys.g_tick_count++;
	// update the HAL timer, if someone need it
	uwTick++;
}

void task_delay(uint32_t tick_count)
{
	__disable_irq();
	if(Asys.current_process)
	{
		process[Asys.current_process].block_count = Asys.g_tick_count + tick_count;
		process[Asys.current_process].current_state = PROCESS_BLOCKED_STATE;
		schedule();
	}
	__enable_irq();
}

void unblock_tasks(void)
{
register uint8_t	i,j;

	for( i = 1 ; i < MAX_PROCESS ; i++)
	{
		if((process[i].wait_event & SUSPEND_ON_TIMER) == SUSPEND_ON_TIMER)
		{
			for( j = 0 ; j < MAX_TIMERS ; j++)
			{
				if((process[i].timer_flags[j] & TIMERFLAGS_IN_USE ) == TIMERFLAGS_IN_USE)
				{
					if((process[i].timer_flags[j] & TIMERFLAGS_ENABLED ) == TIMERFLAGS_ENABLED)
					{
						if(process[i].current_timer[j] == Asys.g_tick_count)
						{
							process[i].current_state = PROCESS_READY_STATE;
							if ((process[i].timer_flags[j] & TIMERFLAGS_FOREVER ) == TIMERFLAGS_FOREVER)
							{
								process[i].current_timer[j] = Asys.g_tick_count + process[i].timer_value[j];
							}
							process[i].timer_expired |= (1<<j);
							process[i].wakeup_rsn |= WAKEUP_FROM_TIMER;
							process[i].wakeup_flags = j;
						}
					}
					else
						process[i].current_timer[j]++;
				}
			}
		}
	}
}
void  SysTick_Handler(void)
{
	if ( Asys.g_os_started )
	{
		update_global_tick_count();
		unblock_tasks();
		//pend the pendsv exception
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	}
	else
		HAL_IncTick();
}

uint32_t create_timer(uint8_t timer_id,uint32_t tick_count,uint8_t flags)
{
uint8_t timer_index = 0;
	if (( process[Asys.current_process].timer_flags[timer_id] & TIMERFLAGS_IN_USE ) == TIMERFLAGS_IN_USE)
		return 1;
	switch(timer_id)
	{
	case	TIMER_ID_0:	timer_index = 0; break;
	case	TIMER_ID_1:	timer_index = 1; break;
	case	TIMER_ID_2:	timer_index = 2; break;
	case	TIMER_ID_3:	timer_index = 3; break;
	case	TIMER_ID_4:	timer_index = 4; break;
	case	TIMER_ID_5:	timer_index = 5; break;
	case	TIMER_ID_6:	timer_index = 6; break;
	case	TIMER_ID_7:	timer_index = 7; break;
	default : return 1;
	}
	__disable_irq();
	process[Asys.current_process].timer_flags[timer_index] = (flags & TIMERFLAGS_USERMASK) | TIMERFLAGS_IN_USE;
	process[Asys.current_process].timer_value[timer_index] = tick_count;
	process[Asys.current_process].current_timer[timer_index] = Asys.g_tick_count + tick_count;
	__enable_irq();
	return 0;
}

uint32_t start_timer(uint8_t timer_id)
{
uint8_t timer_index = 0;
	if (( process[Asys.current_process].timer_flags[timer_id] & TIMERFLAGS_IN_USE ) == TIMERFLAGS_IN_USE)
		return 1;
	switch(timer_id)
	{
	case	TIMER_ID_0:	timer_index = 0; break;
	case	TIMER_ID_1:	timer_index = 1; break;
	case	TIMER_ID_2:	timer_index = 2; break;
	case	TIMER_ID_3:	timer_index = 3; break;
	case	TIMER_ID_4:	timer_index = 4; break;
	case	TIMER_ID_5:	timer_index = 5; break;
	case	TIMER_ID_6:	timer_index = 6; break;
	case	TIMER_ID_7:	timer_index = 7; break;
	default : return 1;
	}
	process[Asys.current_process].timer_flags[timer_index] |= TIMERFLAGS_ENABLED;
	return 0;
}

uint32_t restart_timer(uint8_t timer_id,uint32_t tick_count,uint8_t flags)
{
	if (( process[Asys.current_process].timer_flags[timer_id] & TIMERFLAGS_IN_USE ) != TIMERFLAGS_IN_USE)
		return 1;
	process[Asys.current_process].timer_flags[timer_id] &= ~TIMERFLAGS_IN_USE;
	create_timer(timer_id,tick_count,flags);
	return 0;
}

uint32_t stop_timer(uint8_t timer_id)
{
	process[Asys.current_process].timer_flags[timer_id] &= ~TIMERFLAGS_ENABLED;
	return 0;
}

uint32_t destroy_timer(uint8_t timer_id)
{
	__disable_irq();
	process[Asys.current_process].timer_flags[timer_id] = 0;
	__enable_irq();
	return 0;
}

uint8_t get_timer_expired(void)
{
uint8_t tim_exp = process[Asys.current_process].timer_expired;
	process[Asys.current_process].timer_expired &= ~tim_exp;
	return tim_exp;
}
