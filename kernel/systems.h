/*
 * systems.h
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#ifndef KERNEL_SYSTEMS_H_
#define KERNEL_SYSTEMS_H_

#ifdef	STM32H563xx
/* defines for memory pool, in bottom of ram */
/* The pool should be aligned on 64K boundary if possible */
/* Note : RAM_START must be equal to osMemPool in ld file */
#define RAM_START               0x20090000U
#define SIZE_RAM                ( (32) * (1024))
#define RAM_END                 ((RAM_START) + (SIZE_RAM) )
#define	POOL_START			    RAM_START
#define	POOL_END			    RAM_END
#define	POOL_SIZE			    256
#define	POOL_NUM			    (RAM_END-RAM_START)/POOL_SIZE
#define POOL_RAM				__attribute__((section(".osMemPool"))) __attribute__ ((aligned (32)))
/* defines for system & stack pool, in top of ram */
/* Stacks start from top
 * At the bottom there are the OS structures:
 * MEMpool	: 	8 uint8_t
 * process	: 	14 uint32_t
 * Asys		:	9 uint32_t equiv
 * HWMngr	:	9 uint32_t equiv
 * Starting from bottom :
 * In the case above :
 * MEMpool * POOL_NUM ( 1024 bytes ) + process ( 56bytes ) + Asys ( 36 bytes ) + HWMngr ( 36 bytes )
 * So 2048 bytes are enough
 */
/* Note : SRAM_START must be equal to osSegment in ld file */
#define SRAM_START               0x2009C000U
#define SIZE_STACKS              ( (16) * (1024))
#define SRAM_END                 ((SRAM_START) + (SIZE_STACKS) )
#define SIZE_PROCESS_STACK       2048U
#define SIZE_SCHED_STACK         2048U
#define P1_STACK_START           SRAM_END
#define P2_STACK_START           ( (SRAM_END) - (1 * SIZE_PROCESS_STACK) )
#define P3_STACK_START           ( (SRAM_END) - (2 * SIZE_PROCESS_STACK) )
#define P4_STACK_START           ( (SRAM_END) - (3 * SIZE_PROCESS_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_PROCESS_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_PROCESS_STACK) )
#define SYSTEM_RAM				__attribute__((section(".osSegment"))) __attribute__ ((aligned (32)))
/* In the case above we have6 stacks ( 12Kbytes )  and the area is 16Kbytes, the structures can be placed
 * at the beginning of osSegment
 */

#define	DEBUG_GPIOPORT			PG6_Debug_GPIO_Port
#define	DEBUG_GPIOBIT			PG6_Debug_Pin
#define	LED_1_GPIOPORT			LED3_RED_GPIO_Port
#define	LED_1_GPIOBIT			LED3_RED_Pin
#define	LED_2_GPIOPORT			LED1_GREEN_GPIO_Port
#define	LED_2_GPIOBIT			LED1_GREEN_Pin
#define	LED_3_GPIOPORT			LED2_YELLOW_GPIO_Port
#define	LED_3_GPIOBIT			LED2_YELLOW_Pin

#define TICK_HZ 				1000U
#define HSI_CLOCK         		160000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK

//#define	LWIP_ENABLED			1
#define	USBDEV_ENABLED			1
#define	USBDEV_IS_FS			1
//#define	USBHOST_ENABLED			1

#define	PendSV_PRIORITY			15
#define	SysTick_PRIORITY		14
#define	ASSIGNED				1
#endif

#ifdef	STM32F746xx
/* defines for memory pool, in bottom of ram */
/* The pool should be aligned on 64K boundary if possible */
/* Note : RAM_START must be equal to osMemPool in ld file */
#define RAM_START               0x20040000U
#define SIZE_RAM                ( (32) * (1024))
#define RAM_END                 ((RAM_START) + (SIZE_RAM) )
#define	POOL_START			    RAM_START
#define	POOL_END			    RAM_END
#define	POOL_SIZE			    256
#define	POOL_NUM			    (RAM_END-RAM_START)/POOL_SIZE
#define POOL_RAM				__attribute__((section(".osMemPool"))) __attribute__ ((aligned (32)))
/* defines for system & stack pool, in top of ram */
/* Stacks start from top and last 12K ( SIZE_PROCESS_STACK * 6 )
 * At the bottom there are the OS structures:
 * MEMpool	: 	8 uint8_t
 * process	: 	14 uint32_t
 * Asys		:	9 uint32_t equiv
 * HWMngr	:	9 uint32_t equiv
 */
/* Note : SRAM_START must be equal to osSegment in ld file */
#define SRAM_START               0x2004C000U
#define SIZE_STACKS              ( (16) * (1024))
#define SRAM_END                 ((SRAM_START) + (SIZE_STACKS) )
#define SIZE_PROCESS_STACK       2048U
#define SIZE_SCHED_STACK         2048U
#define P1_STACK_START           SRAM_END
#define P2_STACK_START           ( (SRAM_END) - (1 * SIZE_PROCESS_STACK) )
#define P3_STACK_START           ( (SRAM_END) - (2 * SIZE_PROCESS_STACK) )
#define P4_STACK_START           ( (SRAM_END) - (3 * SIZE_PROCESS_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_PROCESS_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_PROCESS_STACK) )
#define SYSTEM_RAM				__attribute__((section(".osSegment"))) __attribute__ ((aligned (32)))
/* In the case above :
 * we have 6 stacks ( 12Kbytes )  and the area is 16Kbytes, the structures can be placed
 * at the beginning of osSegment
 * In the case above :
 * MEMpool * POOL_NUM ( 1024 bytes ) + process ( 56bytes ) + Asys ( 36 bytes ) + HWMngr ( 36 bytes )
 * So 2048 bytes are enough starting from SRAM_START
 */

#define	DEBUG_GPIOPORT			PG6_Debug_GPIO_Port
#define	DEBUG_GPIOBIT			PG6_Debug_Pin
#define	LED_1_GPIOPORT			LED3_RED_GPIO_Port
#define	LED_1_GPIOBIT			LED3_RED_Pin
#define	LED_2_GPIOPORT			LED1_GREEN_GPIO_Port
#define	LED_2_GPIOBIT			LED1_GREEN_Pin
#define	LED_3_GPIOPORT			LED2_YELLOW_GPIO_Port
#define	LED_3_GPIOBIT			LED2_YELLOW_Pin

#define TICK_HZ 				1000U
#define HSI_CLOCK         		200000000U
#define SYSTICK_TIM_CLK   		HSI_CLOCK

//#define	LWIP_ENABLED			1
#define	USBDEV_ENABLED			1
//#define	USBDEV_IS_FS			1
//#define	USBHOST_ENABLED			1

#define	PendSV_PRIORITY			15
#define	SysTick_PRIORITY		14
#define	ASSIGNED				1
#endif

#ifndef ASSIGNED
#error "Processor not implemented"
#endif
#endif /* KERNEL_SYSTEMS_H_ */
