#ifndef API_INC_ERROR_HANDLER_H_
#define API_INC_ERROR_HANDLER_H_

#include "stm32f4xx_hal.h"
#include "typedefs.h"

bool_t read_error_flag(void);
void write_error_flag(bool_t value);
void Error_Handler(void);

#endif /* API_INC_ERROR_HANDLER_H_ */
