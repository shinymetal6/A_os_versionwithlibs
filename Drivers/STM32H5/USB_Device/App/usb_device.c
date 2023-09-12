#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"

#include "main.h"

extern PCD_HandleTypeDef hpcd_USB_DRD_FS;

USBD_HandleTypeDef hUsbDeviceFS;
extern USBD_DescriptorsTypeDef HID_Desc;

extern	USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;
extern	USBD_DescriptorsTypeDef CDC_Desc;

void MX_USB_Device_Init(void)
{
  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &CDC_Desc, 0) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  {
    Error_Handler();
  }

  HAL_PWREx_EnableVddUSB();
}
