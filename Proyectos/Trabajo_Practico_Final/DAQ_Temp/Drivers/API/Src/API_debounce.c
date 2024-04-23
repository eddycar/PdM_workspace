#include "API_debounce.h"
#include "API_delay.h"

#define DEBOUNCE_TIME 40

typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING,
} debounceState_t;

static debounceState_t currentState;
static delay_t debounceDelay;
static bool_t buttonPressed = false;

void debounceFSM_init(void) {
	currentState = BUTTON_UP; //current state initializes
	delayInit(&debounceDelay, DEBOUNCE_TIME); // 40 second timer initializes
}

void debounceFSM_update(void) {
	switch (currentState) {
	case BUTTON_UP: //initial state: Button Up - High Logic State
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) { // Read User Button state
			delayRead(&debounceDelay); //Starts timing 40 seconds
			currentState = BUTTON_FALLING; //Changes State
		}
		break;
	case BUTTON_FALLING: // Button Pressed
		if (delayRead(&debounceDelay)) { // Was it 40 seconds?
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) { // Read User Button state
				currentState = BUTTON_DOWN; //Changes State
				buttonPressed= true;
			} else {
				currentState = BUTTON_UP; //High Logic State
			}
		}
		break;
	case BUTTON_DOWN: // Low Logic Level
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) { // Read User Button state
			delayWrite(&debounceDelay, DEBOUNCE_TIME); // Restart timing 40 seconds
			currentState = BUTTON_RAISING; // Changes State
		}
		break;
	case BUTTON_RAISING: // Button Released
		if (delayRead(&debounceDelay)) { // Was it 40 seconds?
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) { // Read User Button state
				currentState = BUTTON_UP; // Changes State
				buttonPressed= false;

			} else {
				currentState = BUTTON_DOWN; // Low Logic State
			}
		}
		break;
	}
}

bool_t readKey(void) {
	return buttonPressed;
}
