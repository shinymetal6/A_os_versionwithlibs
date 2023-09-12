/*
 * A.c
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */
#include "main.h"
#include "A.h"
#include "systems.h"
#include "scheduler.h"

SYSTEM_RAM	PCB_t 		process[MAX_PROCESS];
SYSTEM_RAM	Asys_t		Asys;
SYSTEM_RAM	MEMpool_t	MEMpool[POOL_NUM];
SYSTEM_RAM	HWMngr_t	HWMngr[PERIPHERAL_NUM];

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack)
{
     __set_MSP(sched_top_of_stack);
     __asm volatile("BX LR");
}

void init_processes_stacks(void)
{
uint32_t *pPSP,i,j;
	process[0].current_state = PROCESS_READY_STATE;
	process[1].current_state = PROCESS_READY_STATE;
	process[2].current_state = PROCESS_READY_STATE;
	process[3].current_state = PROCESS_READY_STATE;
	process[4].current_state = PROCESS_READY_STATE;

	process[0].psp_value = IDLE_STACK_START;
	process[1].psp_value = T1_STACK_START;
	process[2].psp_value = T2_STACK_START;
	process[3].psp_value = T3_STACK_START;
	process[4].psp_value = T4_STACK_START;

	process[0].task_handler = supervisor;
	process[1].task_handler = process_1;
	process[2].task_handler = process_2;
	process[3].task_handler = process_3;
	process[4].task_handler = process_4;

	for(i = 0 ; i < MAX_TASKS ;i++)
	{
		pPSP = (uint32_t*) process[i].psp_value;
		pPSP--;
		*pPSP = DUMMY_XPSR;//0x00100000
		pPSP--; //PC
		*pPSP = (uint32_t) process[i].task_handler;
		pPSP--; //LR
		*pPSP = 0xFFFFFFFD;
		for(j = 0 ; j < 13 ; j++)
		{
			pPSP--;
			*pPSP = 0;
		}
		process[i].psp_value = (uint32_t)pPSP;
	}
}

void init_systick_timer(uint32_t tick_hz)
{
uint32_t ticks = (SYSTICK_TIM_CLK/tick_hz)-1;
    SysTick_Config(ticks);
    Asys.g_os_started = 1;
}

void A_init_mem(void)
{
	A_bzero((uint8_t *)&Asys,sizeof(Asys));
	A_bzero((uint8_t *)HWMngr,sizeof(HWMngr));
	A_bzero((uint8_t *)process,sizeof(process));
	A_bzero((uint8_t *)(SCHED_STACK_START-SIZE_TASK_STACK),SIZE_TASK_STACK*MAX_PROCESS);
}

void A_start(void)
{
	__disable_irq();
	HAL_NVIC_SetPriority(PendSV_IRQn,  PendSV_PRIORITY, 0);		/* Make PendSV_IRQn lower priority */
	HAL_NVIC_SetPriority(SysTick_IRQn, SysTick_PRIORITY, 0);	/* Make PendSV_IRQn lower priority */

	init_scheduler_stack(SCHED_STACK_START);
	init_processes_stacks();
	init_systick_timer(TICK_HZ);
	mem_init();
	switch_sp_to_psp();

	__enable_irq();
	supervisor();
}
