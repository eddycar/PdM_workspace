#include "API_uart.h"

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
static void SystemClock_Config(void);
static void Error_Handler(void);

// Function Prototypes
static void uartErrorHandler();
static void printUARTConfiguration(UART_HandleTypeDef UartHandle); // function To print the UART configuratión

//Configure the UART peripheral
bool_t uartInit() {

	bool_t isConnectionSuccesfull = true;

	UartHandle.Instance = USARTx; //Put the USART peripheral in the Asynchronous mode (UART Mode)
	UartHandle.Init.BaudRate = 9600;                   // BaudRate configuration
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B; // Word Length = 8 Bits (7 data bit + 1 parity bit) :
													 // BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	UartHandle.Init.StopBits = UART_STOPBITS_1;     // One Stop bit
	UartHandle.Init.Parity = UART_PARITY_ODD;      // ODD parity
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE; // Hardware flow control disabled (RTS and CTS signals)
	UartHandle.Init.Mode = UART_MODE_TX_RX;   // Transmission and reception mode
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;	// Oversampling = 16

	if (HAL_UART_Init(&UartHandle) != HAL_OK) { // handling Error
		uartErrorHandler();
		isConnectionSuccesfull = false;
	}else {
		printUARTConfiguration(UartHandle); // If the serial conection is successful, print uart configuration
	}
	return isConnectionSuccesfull;
}

void uartSendString(uint8_t *pstring) { // Prints String through serial port
	if (pstring == NULL) {
		uartErrorHandler(); // Handling Error
	}
	while (*pstring != '\0') {
		HAL_UART_Transmit(&UartHandle, pstring++, 1, HAL_MAX_DELAY); // Prints character by character through serial port
	}
}

void uartSendStringSize(uint8_t *pstring, uint16_t size) { // Prints String with user-defined length through serial port
	if (pstring == NULL) {
		uartErrorHandler(); // Handling Error
	}
	for (uint16_t i = 0; i < size; i++) {
		HAL_UART_Transmit(&UartHandle, pstring++, 1, HAL_MAX_DELAY); // Prints character by character up to user-defined length through serial port
	}
}

// Function to redirect the standar output to the usart module
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

void printUARTConfiguration(UART_HandleTypeDef UartHandle) {
	// print configuration parameters through serial terminal
    printf("\rConfiguracion del UART:\n");
    printf("\rBaudRate: %lu\n", UartHandle.Init.BaudRate);
    printf("\rWordLength: %d bits\n", (UartHandle.Init.WordLength == UART_WORDLENGTH_8B) ? 8 : 9);
    printf("\rStopBits: %s\n", (UartHandle.Init.StopBits == UART_STOPBITS_1) ? "1 bit" : "2 bits");
    printf("\rParity: %s\n", (UartHandle.Init.Parity == UART_PARITY_NONE) ? "Ninguno" : (UartHandle.Init.Parity == UART_PARITY_EVEN) ? "Par" : "Impar");
    printf("\rControl de flujo: %s\n", (UartHandle.Init.HwFlowCtl == UART_HWCONTROL_NONE) ? "Deshabilitado" : "Habilitado");
    printf("\rModo: %s\n", (UartHandle.Init.Mode == UART_MODE_TX) ? "Transmision" : (UartHandle.Init.Mode == UART_MODE_RX) ? "Recepcion" : "Transmision y Recepcion");
    printf("\rOversampling: %d\n", (UartHandle.Init.OverSampling == UART_OVERSAMPLING_16) ? 16 : 8);
}

static void uartErrorHandler() {
	/* Turn LED3 on */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET );
	while (1) {
	}
}

