/*
 * weak_processes.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */


#include "main.h"
#include "../../A_os/kernel/A.h"

/* These processes waste only time, they are defined to have something of useless to schedule */
__weak void weak_process1(uint32_t process_id)
{
	while(1);
}
__weak void weak_process2(uint32_t process_id)
{
	while(1);
}
__weak void weak_process3(uint32_t process_id)
{
	while(1);
}
__weak void weak_process4(uint32_t process_id)
{
	while(1);
}

/* This processes table is define as weak so can be overridden by a user defined processes table */
__weak USRprcs_t	UserProcesses[USR_PROCESS_NUMBER] =
{
		{
				.user_process = weak_process1,
				.stack_size = 256,
		},
		{
				.user_process = weak_process2,
				.stack_size = 256,
		},
		{
				.user_process = weak_process3,
				.stack_size = 256,
		},
		{
				.user_process = weak_process4,
				.stack_size = 256,
		}
};

