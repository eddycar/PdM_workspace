/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FINITE_STATE_MACHINE.h"

int main(void) {

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Initialize Finite State Machine */
	SystemFSM_init();

	/* Infinite loop */
	while (1) {
		SystemFSM_update();
	}
}
