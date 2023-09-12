/*
 * systems.h
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#ifndef KERNEL_SYSTEMS_H_
#define KERNEL_SYSTEMS_H_

#ifdef	STM32H563xx
/*
	Include paths:
	USB :
	../../A_os/Libraries/STM32H5/STM32_USB_Device_Library/Class/CDC/Inc
	../../A_os/Drivers/STM32H5/USB_Device/Target
	../../A_os/Libraries/STM32H5/STM32_USB_Device_Library/Core/Inc
*/
/* defines for memory pool, in bottom of sram4 */
#define RAM_START               0x20080000U
#define SIZE_RAM                ( (32) * (1024))
#define RAM_END                 ((RAM_START) + (SIZE_RAM) )
#define	POOL_START			    RAM_START
#define	POOL_END			    RAM_END
#define	POOL_SIZE			    256
#define	POOL_NUM			    (RAM_END-RAM_START)/POOL_SIZE
/* defines for stack pool, in top of sram4 */
#define SIZE_SRAM                ( (128) * (1024))
#define SRAM_START               0x20080000U
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )
#define SIZE_TASK_STACK          2048U
#define SIZE_SCHED_STACK         2048U
#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )
#define SYSTEM_RAM				__attribute__((section(".sram_4" ))) __attribute__ ((aligned (32)))

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

#define	PendSV_PRIORITY			15
#define	SysTick_PRIORITY		14
#define	ASSIGNED				1
#endif

#endif /* KERNEL_SYSTEMS_H_ */
