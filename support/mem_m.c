/*
 * mem_m.c
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#include "main.h"

void A_bzero(uint8_t *ptr,uint16_t count)
{
	while(count)
	{
		*ptr++ = 0;
		count--;
	}
}

void A_memcpy(uint8_t *dest,uint8_t *source,uint16_t size)
{
	while(size)
	{
		*dest++=*source++;
		size--;
	}
}
