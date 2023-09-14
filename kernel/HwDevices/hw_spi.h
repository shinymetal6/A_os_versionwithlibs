/*
 * hw_spi.h
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#ifndef KERNEL_HWDEVICES_HW_SPI_H_
#define KERNEL_HWDEVICES_HW_SPI_H_

extern	SPI_HandleTypeDef		hspi1;
#define	ST25R3915_SPI			hspi1

#define HW_SPI_ERROR_NONE                     0
#define HW_SPI_ERROR_BUS_FAILURE             -1
#define HW_SPI_ERROR_WRONG_PARAM             -2
#define HW_SPI_ERROR_FEATURE_NOT_SUPPORTED   -3
#define HW_SPI_ERROR_HW_NOT_OWNED			 -4

#define HW_SPI_TIMEOUT        2000U /* baud rate of SPI1 = 5 Mbps*/

#endif /* KERNEL_HWDEVICES_HW_SPI_H_ */
