/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           USB_Device/HID_Standalone/USB_Device/App/usb_device.h
  * @author         MCD Application Team
  * @brief          Header for usb_device.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DEVICE__H__
#define __USB_DEVICE__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx.h"
#include "stm32h5xx_hal.h"
#include "usbd_def.h"

void MX_USB_Device_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* __USB_DEVICE__H__ */
