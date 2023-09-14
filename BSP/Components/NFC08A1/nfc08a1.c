/*
 * nfc08a1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "nfc08a1.h"

void nfc08a1_A_led_on(void)
{
	  HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, GPIO_PIN_SET);
}

void nfc08a1_A_led_off(void)
{
	  HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, GPIO_PIN_RESET);
}

void nfc08a1_B_led_on(void)
{
	  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);
}

void nfc08a1_B_led_off(void)
{
	  HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET);
}

void nfc08a1_F_led_on(void)
{
	  HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, GPIO_PIN_SET);
}

void nfc08a1_F_led_off(void)
{
	  HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, GPIO_PIN_RESET);
}

void nfc08a1_V_led_on(void)
{
	  HAL_GPIO_WritePin(LED_V_GPIO_Port, LED_V_Pin, GPIO_PIN_SET);
}

void nfc08a1_V_led_off(void)
{
	  HAL_GPIO_WritePin(LED_V_GPIO_Port, LED_V_Pin, GPIO_PIN_RESET);
}

void nfc08a1_AP2P_led_on(void)
{
	  HAL_GPIO_WritePin(LED_AP2P_GPIO_Port, LED_AP2P_Pin, GPIO_PIN_SET);
}

void nfc08a1_AP2P_led_off(void)
{
	  HAL_GPIO_WritePin(LED_AP2P_GPIO_Port, LED_AP2P_Pin, GPIO_PIN_RESET);
}

void nfc08a1_Field_led_on(void)
{
	  HAL_GPIO_WritePin(LED_FIELD_GPIO_Port, LED_FIELD_Pin, GPIO_PIN_SET);
}

void nfc08a1_Field_led_off(void)
{
	  HAL_GPIO_WritePin(LED_FIELD_GPIO_Port, LED_FIELD_Pin, GPIO_PIN_RESET);
}

