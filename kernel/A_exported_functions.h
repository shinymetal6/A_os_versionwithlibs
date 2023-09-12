/*
 * A_exported_functions.h
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#ifndef KERNEL_A_EXPORTED_FUNCTIONS_H_
#define KERNEL_A_EXPORTED_FUNCTIONS_H_

/* System */
extern	uint32_t wait_event(uint32_t events);
extern	uint8_t get_current_process(void);

/* Memory */
extern	uint8_t *mem_get(uint32_t size );
extern	uint32_t mem_release(uint8_t *data_ptr);

/* timer */
extern	void task_delay(uint32_t tick_count);
extern	uint32_t create_timer(uint8_t timer_id,uint32_t tick_count,uint8_t flags);

/* timer id */
#define	TIMER_ID_0		0x01
#define	TIMER_ID_1		0x02
#define	TIMER_ID_2		0x04
#define	TIMER_ID_3		0x08
#define	TIMER_ID_4		0x10
#define	TIMER_ID_5		0x20
#define	TIMER_ID_6		0x40
#define	TIMER_ID_7		0x80

/* timer flags */
#define	TIMERFLAGS_ONESHOT			0x00
#define	TIMERFLAGS_FOREVER			0x01
#define	TIMERFLAGS_ENABLED			0x02
#define	TIMERFLAGS_IN_USE			0x80
#define	TIMERFLAGS_DISABLED			0x00
#define	TIMERFLAGS_USERMASK			0x0f

/* hwmanager : usb */
extern	uint32_t send_usb(uint8_t* ptr, uint16_t len);
extern	uint32_t set_usb_rx_buffer(uint8_t *rx_buf);

/* peripherals */
#define	HW_DELAY					0
#define	HW_TIMER					1
#define	HW_MBX						2
#define	HW_UART1					3
#define	HW_UART2					4
#define	HW_UART3					5
#define	HW_I2C1						6
#define	HW_I2C2						7
#define	HW_SPI1						8
#define	HW_SPI2						9
#define	HW_USB						31

/* event to wait */
#define	EVENT_DELAY					(1<<HW_DELAY)
#define	EVENT_TIMER					(1<<HW_TIMER)
#define	EVENT_MBX					(1<<HW_MBX)
#define	EVENT_UART1_IRQ				(1<<HW_UART1)
#define	EVENT_UART2_IRQ				(1<<HW_UART2)
#define	EVENT_UART3_IRQ				(1<<HW_UART3)
#define	EVENT_I2C1_IRQ				(1<<HW_I2C1)
#define	EVENT_I2C2_IRQ				(1<<HW_I2C2)
#define	EVENT_SPI1_IRQ				(1<<HW_SPI1)
#define	EVENT_SPI2_IRQ				(1<<HW_SPI2)
#define	EVENT_USB_IRQ				(1<<HW_USB)
/* suspend_mode */
#define	SUSPEND_ON_DELAY			EVENT_DELAY
#define	SUSPEND_ON_TIMER			EVENT_TIMER
#define	SUSPEND_ON_MBX				EVENT_MBX
#define	SUSPEND_ON_UART1_IRQ		EVENT_UART1_IRQ
#define	SUSPEND_ON_UART2_IRQ		EVENT_UART2_IRQ
#define	SUSPEND_ON_UART3_IRQ		EVENT_UART3_IRQ
#define	SUSPEND_ON_I2C1_IRQ			EVENT_I2C1_IRQ
#define	SUSPEND_ON_I2C2_IRQ			EVENT_I2C2_IRQ
#define	SUSPEND_ON_SPI1_IRQ			EVENT_SPI1_IRQ
#define	SUSPEND_ON_SPI2_IRQ			EVENT_SPI2_IRQ
#define	SUSPEND_ON_USB_IRQ			EVENT_USB_IRQ
/* wakeup_flags */
#define	WAKEUP_FROM_DELAY			SUSPEND_ON_DELAY
#define	WAKEUP_FROM_TIMER			SUSPEND_ON_TIMER
#define	WAKEUP_FROM_MBX				SUSPEND_ON_MBX
#define	WAKEUP_FROM_UART1_IRQ		SUSPEND_ON_UART1_IRQ
#define	WAKEUP_FROM_UART2_IRQ		SUSPEND_ON_UART2_IRQ
#define	WAKEUP_FROM_UART3_IRQ		SUSPEND_ON_UART3_IRQ
#define	WAKEUP_FROM_I2C1_IRQ		SUSPEND_ON_I2C1_IRQ
#define	WAKEUP_FROM_I2C2_IRQ		SUSPEND_ON_I2C2_IRQ
#define	WAKEUP_FROM_SPI1_IRQ		SUSPEND_ON_SPI1_IRQ
#define	WAKEUP_FROM_SPI2_IRQ		SUSPEND_ON_SPI2_IRQ
#define	WAKEUP_FROM_USB_IRQ			SUSPEND_ON_USB_IRQ
/* device_flags */
#define	DEVICE_DELAY				HW_DELAY
#define	DEVICE_TIMER				HW_TIMER
#define	DEVICE_MBX					HW_MBX
#define	DEVICE_UART1				HW_UART1
#define	DEVICE_UART2				HW_UART2
#define	DEVICE_UART3				HW_UART3
#define	DEVICE_I2C1					HW_I2C1
#define	DEVICE_I2C2					HW_I2C2
#define	DEVICE_SPI1					HW_SPI1
#define	DEVICE_SPI2					HW_SPI2
#define	DEVICE_USB					HW_USB

#endif /* KERNEL_A_EXPORTED_FUNCTIONS_H_ */
