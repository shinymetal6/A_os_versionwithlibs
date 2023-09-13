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

void supervisor(void)
{
	while(1)
	{
		if ( Asys.num_buf_in_use == 0 )
			defrag_mem();

		MX_LWIP_Process();
	}
}

