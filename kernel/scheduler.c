/*
 * scheduler.c
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

uint32_t get_psp_value(void)
{
	return process[Asys.current_process].psp_value;
}

void save_psp_value(uint32_t current_psp_value)
{
	process[Asys.current_process].psp_value = current_psp_value;
}

void update_next_task(void)
{
	int state = 0;

	for(int i= 0 ; i < (MAX_TASKS) ; i++)
	{
		Asys.current_process++;
		Asys.current_process %= MAX_TASKS;
		/******************************************************************/
		if ( Asys.current_process == 0 )
			return;
		/******************************************************************/
		state = process[Asys.current_process].current_state;
		if (( state & PROCESS_KILLED_STATE ) != PROCESS_KILLED_STATE)
		{
			if( ((state & PROCESS_READY_STATE )== PROCESS_READY_STATE) && (Asys.current_process != 0) )
				break;
		}
	}
	if((state & PROCESS_READY_STATE ) != PROCESS_READY_STATE)
		Asys.current_process = 0;
}

__attribute__((naked)) void switch_sp_to_psp(void)
{
    //1. initialize the PSP with TASK1 stack start address

	//get the value of psp of current_task
	__asm volatile ("PUSH {LR}"); //preserve LR which connects back to main()
	__asm volatile ("BL get_psp_value");
	__asm volatile ("MSR PSP,R0"); //initialize psp
	__asm volatile ("POP {LR}");  //pops back LR value
	//2. change SP to PSP using CONTROL register
	__asm volatile ("MOV R0,#0X02");
	__asm volatile ("MSR CONTROL,R0");
	__asm volatile ("BX LR");
}

void schedule(void)
{
	//pend the pendsv exception
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

__attribute__((naked)) void PendSV_Handler(void)
{
	/*Save the context of current task */
	//1. Get current running task's PSP value
	__asm volatile("MRS R0,PSP");
	//2. Using that PSP value store SF2( R4 to R11)
	__asm volatile("STMDB R0!,{R4-R11}");
	__asm volatile("PUSH {LR}");
	//3. Save the current value of PSP
    __asm volatile("BL save_psp_value");
	/*Retrieve the context of next task */
	//1. Decide next task to run
    __asm volatile("BL update_next_task");
	//2. get its past PSP value
	__asm volatile ("BL get_psp_value");
	//3. Using that PSP value retrieve SF2(R4 to R11)
	__asm volatile ("LDMIA R0!,{R4-R11}");
	//4. update PSP and exit
	__asm volatile("MSR PSP,R0");
	__asm volatile("POP {LR}");
	__asm volatile("BX LR");
}

uint32_t __attribute__ ((noinline)) wait_event(uint32_t events)
{
uint32_t wake;
	__disable_irq();
	process[Asys.current_process].wait_event = events;
	process[Asys.current_process].current_state &= ~PROCESS_READY_STATE;
	schedule();
	wake = process[Asys.current_process].wakeup_rsn;
	process[Asys.current_process].wakeup_rsn = 0;
	__enable_irq();
	return wake;
}


uint32_t inline activate_process(uint8_t dest_process,uint32_t rsn , uint32_t flags)
{
	if (( process[dest_process].current_state & PROCESS_KILLED_STATE ) != PROCESS_KILLED_STATE)
	{
		__disable_irq();
		process[dest_process].wakeup_rsn |= rsn;
		process[dest_process].wakeup_flags |= flags;
		process[dest_process].current_state = 0;
		process[dest_process].current_state |= PROCESS_READY_STATE;
		__enable_irq();
	}
	return 0;
}

uint8_t get_current_process(void)
{
	return Asys.current_process;
}

