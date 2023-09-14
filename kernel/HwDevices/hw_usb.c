/*
 * hw_usb.c
 *
 *  Created on: Sep 12, 2023
 *      Author: fil
 */

#include "main.h"
#include "../A.h"
#include "../scheduler.h"
#include "../A_exported_functions.h"
#include "../hwmanager.h"
#include "../systems.h"

extern	HWMngr_t	HWMngr[PERIPHERAL_NUM];
extern	Asys_t		Asys;

uint32_t hw_set_usb_rx_buffer(uint8_t *rx_buf)
{
	if ( HWMngr[HW_USB].process == Asys.current_process )
	{
		HWMngr[HW_USB].rx_buf = rx_buf;
		return 0;
	}
	return 255;
}

uint32_t hw_UsbPktReceived(uint8_t* Buf, uint32_t Len)
{
uint8_t	*dest_ptr = HWMngr[HW_USB].rx_buf;
	if ( dest_ptr != NULL )
	{
		HWMngr[HW_USB].rxlen = Len;
		A_memcpy(dest_ptr,Buf,Len);
		dest_ptr[Len] = 0;
		activate_process(HWMngr[HW_USB].process,WAKEUP_FROM_USB_IRQ,HW_USB_RX_COMPLETE_FLAG);
		return	Len;
	}
	return 0;
}

void hw_UsbControlCallback(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
}

#if defined USBDEV_ENABLED
	#ifdef USBDEV_IS_FS
		extern	uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);
	#else
		extern	uint8_t CDC_Transmit_HS(uint8_t* Buf, uint16_t Len);
	#endif
#endif

uint32_t hw_send_usb(uint8_t* ptr, uint16_t len)
{
	if (( HWMngr[HW_USB].process == Asys.current_process ) && ( len != 0 ))
	{
#if defined USBDEV_ENABLED
	#ifdef USBDEV_IS_FS
		return (uint32_t )CDC_Transmit_FS(ptr, len);
	#else
		return (uint32_t )CDC_Transmit_HS(ptr, len);
	#endif
#endif
	}
	return 0xffffffff;
}
