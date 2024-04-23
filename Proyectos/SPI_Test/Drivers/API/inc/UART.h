#ifndef API_INC_UART_H_
#define API_INC_UART_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t *pString, uint16_t size);

#endif /* API_INC_UART_H_ */