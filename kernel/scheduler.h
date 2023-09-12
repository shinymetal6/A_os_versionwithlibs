/*
 * scheduler.h
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#ifndef KERNEL_SCHEDULER_H_
#define KERNEL_SCHEDULER_H_

#include "A.h"

typedef struct
{
	uint32_t 	psp_value;
	uint32_t 	block_count;
	uint8_t  	current_state;
	uint32_t	wait_event;
	uint8_t		*mbx[MAILBOX_NUM];
	uint32_t	mbx_size[MAILBOX_NUM];
	uint8_t		mbx_number;
	uint32_t	wakeup_rsn;
	uint32_t	wakeup_flags;
	uint32_t	current_timer[MAX_TIMERS];
	uint32_t	timer_value[MAX_TIMERS];
	uint8_t		timer_flags[MAX_TIMERS];
	uint8_t		timer_expired;
	void (*task_handler)(void);
}PCB_t;

/* timer_flags */
#define	TIMERFLAGS_ONESHOT			0x00
#define	TIMERFLAGS_FOREVER			0x01
#define	TIMERFLAGS_ENABLED			0x02
#define	TIMERFLAGS_IN_USE			0x80
#define	TIMERFLAGS_DISABLED			0x00
#define	TIMERFLAGS_USERMASK			0x0f

#define MAX_TASKS   5
#define PROCESS_READY_STATE  0x00
#define PROCESS_BLOCKED_STATE  0XFF

extern	void unblock_tasks(void);
extern	void switch_sp_to_psp(void);
extern	uint32_t activate_process(uint8_t dest_process,uint32_t rsn , uint32_t flags);

#endif /* KERNEL_SCHEDULER_H_ */
