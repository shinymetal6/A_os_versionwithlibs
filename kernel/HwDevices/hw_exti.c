/*
 * hw_exti.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "hw_spi.h"
#include "../A.h"
#include "../scheduler.h"
#include "../A_exported_functions.h"
#include "../hwmanager.h"
#include "../systems.h"

#if defined NFC_ENABLED

extern	void st25r3916Isr( void );

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	if ( GPIO_Pin == ST25R391X_INT_Pin)
		st25r3916Isr();
}
#endif
