#ifndef API_INC_FINITE_STATE_MACHINE_H_
#define API_INC_FINITE_STATE_MACHINE_H_

typedef enum {
	STATE_CONFIG,
	STATE_FAILURE,
	STATE_IDLE,
	STATE_DATA_ADQUISITION,
	STATE_DATA_SENDING,
	STATE_DATA_STORAGE,
} SystemState_t;

void SystemFSM_init(void); //Load the initial state
void SystemFSM_update(void); // reads the inputs, solves the state transition logic and updates the outputs

#endif /* API_INC_FINITE_STATE_MACHINE_H_ */