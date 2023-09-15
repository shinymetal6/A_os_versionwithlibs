/*
 * svc.c
 *
 *  Created on: Sep 15, 2023
 *      Author: fil
 */

#include "main.h"
#include "A.h"
#include "systems.h"
#include "scheduler.h"
#include "A_exported_functions.h"

__weak int32_t svc_noop_function(int32_t svc_index,int32_t param1 , int32_t param2 , int32_t param3)
{
	return param1 + param2;
}

/*
static int32_t svc_function(int32_t param1 , int32_t param2 )
{
	return param1 + param2;
}
*/
#define	SVC_NUM			4
#define	SVC_INDEX_MIN	0x10
#define	SVC_INDEX_MAX	0x13

/* This processes table is define as weak so can be overridden by a user defined processes table */
__weak SVCfunc_t	SVCfunc[SVC_NUM] =
{
		{
				.svc_func = svc_noop_function,
		},
		{
				.svc_func = svc_noop_function,
		},
		{
				.svc_func = svc_noop_function,
		},
		{
				.svc_func = svc_noop_function,
		}
};

void SVC_Handler_c(uint32_t *pBaseOfStackFrame)
{
int32_t res=0xdeadbeef;
uint8_t svc_number;

	//1. get the return address
	uint8_t *pReturn_addr = (uint8_t*)pBaseOfStackFrame[6];
	//2. decrement the return address by 2 to point to opcode of the SVC instruction in the program memory
	pReturn_addr-=2;
	//3. extract the SVC number (LSByte of the opcode, pReturn_addr is a uint8_t ptr...)
	svc_number = *pReturn_addr;
	if ((svc_number >= SVC_INDEX_MIN) && (svc_number <= SVC_INDEX_MAX))
	{
		res = SVCfunc[svc_number-0x10].svc_func(svc_number-SVC_INDEX_MIN, pBaseOfStackFrame[0],pBaseOfStackFrame[1],pBaseOfStackFrame[2]);
	}
	/* store the result back to stack frame at R0's position */
	pBaseOfStackFrame[0] = res;
}

__attribute__( ( naked ) ) void SVC_Handler( void )
{
	__asm ("MRS r0,PSP");	// we work on PSP
	__asm( "B SVC_Handler_c");
}

static int32_t call_svc_hex10(int32_t param1 , int32_t param2 , int32_t param3)
{
int32_t res;
	__asm volatile("SVC #0X10");
	__asm volatile ("MOV %0,R0": "=r"(res) ::);
	return res;
}

static int32_t call_svc_hex11(int32_t param1 , int32_t param2 , int32_t param3)
{
int32_t res;
	__asm volatile("SVC #0X10");
	__asm volatile ("MOV %0,R0": "=r"(res) ::);
	return res;
}

static int32_t call_svc_hex12(int32_t param1 , int32_t param2 , int32_t param3)
{
int32_t res;
	__asm volatile("SVC #0X10");
	__asm volatile ("MOV %0,R0": "=r"(res) ::);
	return res;
}

static int32_t call_svc_hex13(int32_t param1 , int32_t param2 , int32_t param3)
{
int32_t res;
	__asm volatile("SVC #0X10");
	__asm volatile ("MOV %0,R0": "=r"(res) ::);
	return res;
}

int32_t call_svc(int8_t svc_index,int32_t param1 , int32_t param2 , int32_t param3)
{
int32_t res=0xdeadbeef;
	if ((svc_index >= SVC_INDEX_MIN) && (svc_index <= SVC_INDEX_MAX))
	{
		switch(svc_index)
		{
		case 0x10 : res =  call_svc_hex10( param1,  param2,  param3 );break;
		case 0x11 : res =  call_svc_hex11( param1,  param2,  param3 );break;
		case 0x12 : res =  call_svc_hex12( param1,  param2,  param3 );break;
		case 0x13 : res =  call_svc_hex13( param1,  param2,  param3 );break;
		default : break;
		}
	}
	return res;
}




