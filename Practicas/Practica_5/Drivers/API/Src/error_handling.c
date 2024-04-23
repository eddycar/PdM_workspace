/*
 * error_handling.c
 *
 *  Created on: Mar 17, 2024
 *      Author: ASUS
 */

#include "error_handling.h"
/*
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}