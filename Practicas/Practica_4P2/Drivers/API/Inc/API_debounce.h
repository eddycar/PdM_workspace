#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdbool.h>

typedef bool bool_t;

void debounceFSM_init(void); //Load the initial state
void debounceFSM_update(void); // reads the inputs, solves the state transition logic and updates the outputs
bool_t readKey(void);

#endif /* API_INC_API_DEBOUNCE_H_ */
