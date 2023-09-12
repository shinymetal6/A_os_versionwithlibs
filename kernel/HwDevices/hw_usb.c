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

extern	HWMngr_t	HWMngr[PERIPHERAL_NUM];
extern	Asys_t		Asys;

uint32_t	set_usb_rx_buffer(uint8_t *rx_buf)
{
	if ( HWMngr[HW_USB].process == Asys.current_process )
	{
		HWMngr[HW_USB].rx_buf = rx_buf;
		return 0;
	}
	return 255;
}

uint32_t UsbPktReceived(uint8_t* Buf, uint32_t Len)
{
uint8_t	*dest_ptr = HWMngr[HW_USB].rx_buf;
	if ( dest_ptr != NULL )
	{
		HWMngr[HW_USB].rxlen = Len;
		memcpy(dest_ptr,Buf,Len);
		dest_ptr[Len] = 0;
		activate_process(HWMngr[HW_USB].process,WAKEUP_FROM_USB_IRQ,HW_USB_RX_COMPLETE_FLAG);
		return	Len;
	}
	return 0;
}

void UsbControlCallback(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
}

extern	uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

uint32_t send_usb(uint8_t* ptr, uint16_t len)
{
	if (( HWMngr[HW_USB].process == Asys.current_process ) && ( len != 0 ))
	{
		//return (uint32_t )CDC_Transmit_FS(ptr, len);
	}
	return 0xffffffff;
}
