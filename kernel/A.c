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
#include "A_exported_functions.h"

SYSTEM_RAM	MEMpool_t	MEMpool[POOL_NUM];
SYSTEM_RAM 	PCB_t 		process[MAX_PROCESS];
SYSTEM_RAM	Asys_t		Asys;
SYSTEM_RAM	HWMngr_t	HWMngr[PERIPHERAL_NUM];

extern	USRprcs_t	UserProcesses[USR_PROCESS_NUMBER];

A_IpAddr_t	A_IpAddr =
{
		.IP_ADDR0 		= 192,
		.IP_ADDR1 		= 168,
		.IP_ADDR2		= 10,
		.IP_ADDR3 		= 220,
		.NETMASK_ADDR0	= 255,
		.NETMASK_ADDR1 	= 255,
		.NETMASK_ADDR2 	= 255,
		.NETMASK_ADDR3 	= 0,
		.GW_ADDR0 		= 192,
		.GW_ADDR1 		= 168,
		.GW_ADDR2 		= 10,
		.GW_ADDR3 		= 1
};
A_IpAddr_t	A_DhcpIpAddr;

uint32_t	UsbDeviceId0 = 0xdeadbeef;
uint32_t	UsbDeviceId1 = 0xbeefdead;

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
	process[1].psp_value = P1_STACK_START;
	process[2].psp_value = P2_STACK_START;
	process[3].psp_value = P3_STACK_START;
	process[4].psp_value = P4_STACK_START;

	process[0].task_handler = supervisor;
	process[1].task_handler = supervisor_process1;
	process[2].task_handler = supervisor_process2;
	process[3].task_handler = supervisor_process3;
	process[4].task_handler = supervisor_process4;

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
	A_bzero((uint8_t *)(SCHED_STACK_START-SIZE_PROCESS_STACK),SIZE_PROCESS_STACK*MAX_PROCESS);
}

void A_InitIpAddress(void)
{
	A_bzero((uint8_t *)&Asys,sizeof(Asys));
	A_bzero((uint8_t *)HWMngr,sizeof(HWMngr));
	A_bzero((uint8_t *)process,sizeof(process));
	A_bzero((uint8_t *)(SCHED_STACK_START-SIZE_PROCESS_STACK),SIZE_PROCESS_STACK*MAX_PROCESS);
}

void A_enable_processor_faults(void)
{
	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
	SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA_Msk;
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;
}

void A_start(void)
{
#ifdef	LWIP_ENABLED
	A_InitIpAddress();
	MX_LWIP_Init(&A_IpAddr);
#endif
#ifdef	USBDEV_ENABLED
#ifndef	STM32F746xx
	MX_USB_DEVICE_Init();
#endif
#endif
	__disable_irq();
	HAL_NVIC_SetPriority(PendSV_IRQn,  PendSV_PRIORITY, 0);		/* Make PendSV_IRQn lower priority */
	HAL_NVIC_SetPriority(SysTick_IRQn, SysTick_PRIORITY, 0);	/* Make PendSV_IRQn lower priority */
	A_enable_processor_faults();

	init_scheduler_stack(SCHED_STACK_START);
	init_processes_stacks();
	init_systick_timer(TICK_HZ);
	A_mem_init();
	switch_sp_to_psp();

	__enable_irq();
	supervisor();
}
