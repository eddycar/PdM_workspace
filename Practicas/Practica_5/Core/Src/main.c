#include "main.h"
#include "string.h"
#include "API_delay.h"
#include "API_debounce.h"
#include "API_uart.h"
#include "error_handling.h"

#define MAX_STRING_LENGTH 1

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void buttonPressed(void); // Turn On LED
void buttonReleased(void); // Turn Off LED

//Blinking LED Frequency
delay_t delay1, delay2, delay3;

// Variables to print button state through serial terminal
static char textBtnPressed[] = "\rBoton presionado\n";
static char textBtnReleased[] = "\rBoton liberado\n";

int main(void) {

	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	// Initialize LD1_Pin
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);

	delayInit(&delay1, 100); // 200 milisegundos para LED1
	delayInit(&delay2, 300); // 600 milisegundos para LED2
	delayInit(&delay3, 500); // 1 segundo para LED3

	// Initialize debounce module
	debounceFSM_init();

	// Initialize UART module
	uartInit();

	uint8_t receivedString[MAX_STRING_LENGTH]; //Create a buffer to store the received String
	uint16_t stringLength = MAX_STRING_LENGTH; // Size of the data string to receive

	while (1) {
		uartReceiveStringSize(receivedString, stringLength);
		HAL_Delay(1000);
		uartSendString(receivedString);
		//update debounce module state
		debounceFSM_update();

		if (readKey()) {
			//buttonPressed(); // LEDs sequence 1
		} else {
			//buttonReleased(); // LEDs sequence 2
		}
	}
}

void buttonPressed(void) {
	uartSendString((uint8_t*) textBtnPressed); // print "Botón presionado" through serial terminal

	if (delayRead(&delay1)) { // Check Delay
		HAL_GPIO_TogglePin(GPIOB, LD1_Pin); // Change LED state
		delayWrite(&delay1, 500); // Restart delay
	}
	if (delayRead(&delay2)) { // Check Delay
		HAL_GPIO_TogglePin(GPIOB, LD2_Pin); // Change LED state
		delayWrite(&delay2, 300); // Restart delay
	}
	if (delayRead(&delay3)) { // Check Delay
		HAL_GPIO_TogglePin(GPIOB, LD3_Pin); // Change LED state
		delayWrite(&delay3, 100); // Restart delay
	}

}

void buttonReleased(void) {
	uartSendString((uint8_t*) textBtnReleased); // print "Botón liberado" through serial terminal
	if (delayRead(&delay1)) { // Check Delay
		HAL_GPIO_TogglePin(GPIOB, LD1_Pin); // Change LED state
		delayWrite(&delay1, 300); // Restart delay
	}
	if (delayRead(&delay2)) { // Check Delay
		HAL_GPIO_TogglePin(GPIOB, LD2_Pin); // Change LED state
		delayWrite(&delay2, 100); // Restart delay
	}
	if (delayRead(&delay3)) { // Check Delay
		HAL_GPIO_TogglePin(GPIOB, LD3_Pin); // Change LED state
		delayWrite(&delay3, 500); // Restart delay
	}
}

/*
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}

static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin | LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin : USER_Btn_Pin */
	GPIO_InitStruct.Pin = USER_Btn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
	GPIO_InitStruct.Pin = LD1_Pin | LD3_Pin | LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_PowerSwitchOn_Pin */
	GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_OverCurrent_Pin */
	GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */