/*
 * supervisor.c
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#include "main.h"
#include "A.h"
#include "systems.h"
#include "scheduler.h"

extern	void MX_LWIP_Process(void);
extern	USRprcs_t	UserProcesses[USR_PROCESS_NUMBER];
extern	PCB_t 		process[MAX_PROCESS];

void supervisor(void)
{
	while(1)
	{
		if ( Asys.num_buf_in_use == 0 )
			defrag_mem();
		if ( Asys.failed_process )
		{
			reset_orphaned_chunks(Asys.failed_process);
			Asys.failed_process = Asys.fail_rsn = 0;
		}
#ifdef	LWIP_ENABLED
		MX_LWIP_Process();
#endif
	}
}

void supervisor_process1(void)
{
	UserProcesses[0].user_process(1);
	process[Asys.current_process].current_state = (PROCESS_KILLED_STATE | PROCESS_FINISHED_FLAG);
	while(1);
}

void supervisor_process2(void)
{
	UserProcesses[1].user_process(2);
	process[Asys.current_process].current_state = (PROCESS_KILLED_STATE | PROCESS_FINISHED_FLAG);
	while(1);
}

void supervisor_process3(void)
{
	UserProcesses[2].user_process(3);
	process[Asys.current_process].current_state = (PROCESS_KILLED_STATE | PROCESS_FINISHED_FLAG);
	while(1);
}

void supervisor_process4(void)
{
	UserProcesses[3].user_process(4);
	process[Asys.current_process].current_state = (PROCESS_KILLED_STATE | PROCESS_FINISHED_FLAG);
	while(1);
}

/* faults management */
void HardFault_Handler(void)
{
	process[Asys.current_process].current_state = (PROCESS_KILLED_STATE | PROCESS_HARDFAULT_FLAG);
	Asys.failed_process = Asys.current_process;
	Asys.fail_rsn = PROCESS_HARDFAULT_FLAG;
	Asys.process_hard_fault[Asys.current_process]++;
	schedule();
}

void MemManage_Handler(void)
{
	process[Asys.current_process].current_state = (PROCESS_KILLED_STATE | PROCESS_MEMMANAGE_FLAG);
	Asys.failed_process = Asys.current_process;
	Asys.fail_rsn = PROCESS_HARDFAULT_FLAG;
	Asys.process_mem_manage_fault[Asys.current_process]++;
	schedule();
}

void BusFault_Handler(void)
{
	process[Asys.current_process].current_state = (PROCESS_KILLED_STATE | PROCESS_BUSFAULT_FLAG);
	Asys.failed_process = Asys.current_process;
	Asys.fail_rsn = PROCESS_HARDFAULT_FLAG;
	Asys.process_bus_fault[Asys.current_process]++;
	schedule();
}

void UsageFault_Handler(void)
{
	process[Asys.current_process].current_state = (PROCESS_KILLED_STATE | PROCESS_USAGEFAULT_FLAG);
	Asys.failed_process = Asys.current_process;
	Asys.fail_rsn = PROCESS_HARDFAULT_FLAG;
	Asys.process_usage_fault[Asys.current_process]++;
	schedule();
}
