#include "UART.h"
#include "error_handler.h"

/* UART handler declaration */
UART_HandleTypeDef UartHandle3;

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

static void printUARTConfiguration(UART_HandleTypeDef UartHandle); // function To print the UART configuratión

bool_t uartInit() {
	bool_t isConnectionSuccesfull = true;

	UartHandle3.Instance = USART3;
	UartHandle3.Init.BaudRate = 9600;
	UartHandle3.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle3.Init.StopBits = UART_STOPBITS_1;
	UartHandle3.Init.Parity = UART_PARITY_NONE;
	UartHandle3.Init.Mode = UART_MODE_TX_RX;
	UartHandle3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&UartHandle3) != HAL_OK) {
		write_error_flag(true);
		isConnectionSuccesfull = false;

	} else {
		printUARTConfiguration(UartHandle3); // If the serial conection is successful, print uart configuration
	}
	return isConnectionSuccesfull;
}

void uartSendString(uint8_t *pstring) {
	if (pstring == NULL) {
		write_error_flag(true);
	}
	while (*pstring != '\0') {
		HAL_UART_Transmit(&UartHandle3, pstring++, 1, HAL_MAX_DELAY); // Prints character by character through serial port
	}
}

void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	if (pstring == NULL) {
		write_error_flag(true);
	}
	for (uint16_t i = 0; i < size; i++) {
		HAL_UART_Transmit(&UartHandle3, pstring++, 1, HAL_MAX_DELAY); // Prints character by character up to user-defined length through serial port
	}
}

void uartReceiveStringSize(uint8_t *pString, uint16_t size) {
	HAL_UART_Receive(&UartHandle3, pString, size, HAL_MAX_DELAY);
}

// Function to redirect the standar output to the usart module
PUTCHAR_PROTOTYPE {
	HAL_UART_Transmit(&UartHandle3, (uint8_t*) &ch, 1, 0xFFFF);

	return ch;
}

static void printUARTConfiguration(UART_HandleTypeDef UartHandle) {
	// print configuration parameters through serial terminal
	printf("\rConfiguracion del UART:\n");
	printf("\rBaudRate: %lu\n", UartHandle.Init.BaudRate);
	printf("\rWordLength: %d bits\n",
			(UartHandle.Init.WordLength == UART_WORDLENGTH_8B) ? 8 : 9);
	printf("\rStopBits: %s\n",
			(UartHandle.Init.StopBits == UART_STOPBITS_1) ? "1 bit" : "2 bits");
	printf("\rParity: %s\n",
			(UartHandle.Init.Parity == UART_PARITY_NONE) ? "Ninguno" :
			(UartHandle.Init.Parity == UART_PARITY_EVEN) ? "Par" : "Impar");
	printf("\rControl de flujo: %s\n",
			(UartHandle.Init.HwFlowCtl == UART_HWCONTROL_NONE) ?
					"Deshabilitado" : "Habilitado");
	printf("\rModo: %s\n",
			(UartHandle.Init.Mode == UART_MODE_TX) ? "Transmision" :
			(UartHandle.Init.Mode == UART_MODE_RX) ?
					"Recepcion" : "Transmision y Recepcion");
	printf("\rOversampling: %d\n",
			(UartHandle.Init.OverSampling == UART_OVERSAMPLING_16) ? 16 : 8);
}
