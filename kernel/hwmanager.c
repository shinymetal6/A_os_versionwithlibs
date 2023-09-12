/*
 * hwmanager.c
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#include "main.h"
#include "A.h"
#include "scheduler.h"
#include "A_exported_functions.h"

extern	HWMngr_t	HWMngr[PERIPHERAL_NUM];
extern	Asys_t		Asys;

uint32_t allocate_hw(uint32_t peripheral)
{
	if ( HWMngr[peripheral].process )
		return 0;
	HWMngr[peripheral].process = Asys.current_process;
	HWMngr[peripheral].status = HWMAN_STATUS_ALLOCATED;
	return peripheral;
}

uint32_t deallocate_hw(uint32_t peripheral)
{
	if ( HWMngr[peripheral].process != Asys.current_process )
		return 0;
	HWMngr[peripheral].process = 0;
	HWMngr[peripheral].status = HWMAN_STATUS_FREE;
	return peripheral;
}

uint16_t get_rx_len(uint32_t peripheral)
{
	if ( HWMngr[peripheral].process != Asys.current_process )
		return 0;
	return HWMngr[HW_USB].rxlen;
}

uint32_t get_peripheral_flags(uint32_t peripheral)
{
	if ( HWMngr[peripheral].process != Asys.current_process )
		return 0;
	return HWMngr[HW_USB].flags;
}
