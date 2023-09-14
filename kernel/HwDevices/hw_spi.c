/*
 * hw_spi.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "hw_spi.h"
#include "../A.h"
#include "../scheduler.h"
#include "../A_exported_functions.h"
#include "../hwmanager.h"
#include "../systems.h"

extern	HWMngr_t	HWMngr[PERIPHERAL_NUM];
extern	Asys_t		Asys;

#define	DONT_CHECK_PROCESS	1
int32_t hw_spi_Send(uint8_t *pData, uint16_t Length)
{
uint8_t   tx[256];
#ifndef DONT_CHECK_PROCESS
	if ( HWMngr[HW_SPI1].process != Asys.current_process )
		return HW_SPI_ERROR_HW_NOT_OWNED;
#endif
	if (pData != NULL)
		A_memcpy(tx, pData, Length);
	return HAL_SPI_Transmit(&ST25R3915_SPI, tx, Length, HW_SPI_TIMEOUT);
}

int32_t hw_spi_Recv(uint8_t * const pData, const uint16_t Length)
{
uint8_t   rx[256];
#ifndef DONT_CHECK_PROCESS
	if ( HWMngr[HW_SPI1].process != Asys.current_process )
		return HW_SPI_ERROR_HW_NOT_OWNED;
#endif
	return HAL_SPI_Receive(&ST25R3915_SPI, (pData != NULL) ? (uint8_t *)pData : rx, Length, HW_SPI_TIMEOUT);
}

int32_t hw_spi_SendRecv(const uint8_t * const pTxData, uint8_t * const pRxData, uint16_t Length)
{
#ifndef DONT_CHECK_PROCESS
	if ( HWMngr[HW_SPI1].process != Asys.current_process )
		return HW_SPI_ERROR_HW_NOT_OWNED;
#endif
	if((pTxData != NULL)&&(pRxData != NULL))
		return HAL_SPI_TransmitReceive(&ST25R3915_SPI, (uint8_t *)pTxData, (uint8_t *)pRxData, Length, HW_SPI_TIMEOUT);
	else if ((pTxData != NULL)&&(pRxData == NULL))
		return HAL_SPI_Transmit(&ST25R3915_SPI, (uint8_t *)pTxData, Length, HW_SPI_TIMEOUT);
	else if ((pTxData == NULL)&&(pRxData != NULL))
		return HAL_SPI_Receive(&ST25R3915_SPI, (uint8_t *)pRxData, Length, HW_SPI_TIMEOUT);
	return HW_SPI_ERROR_FEATURE_NOT_SUPPORTED;
}

int32_t hw_spi_Error(void)
{
	return 1;
}

void 	hw_spi_Error_Handler(char * file, int line)
{

}
