/*
 * API_delay.c
 *
 *  Created on: Mar 17, 2024
 *      Author: ASUS
 */

#include "API_delay.h"
#include "error_handling.h"

//Funcion para inicializar variables de delay
void delayInit(delay_t *delay, tick_t duration) {
	if (delay == NULL) {
		Error_Handler();
	}
	delay->running = false;
	delay->duration = duration;
	delay->startTime = 0;
}

//Funcion para monitorear el estado del retardo
bool_t delayRead(delay_t *delay) {
	if (delay == NULL) {                // Se valida que delay se haya inicializado y que sus miembros no sean NULL
		Error_Handler();
	}

	tick_t currentTime = (tick_t) HAL_GetTick(); //Se obtiene la marca de tiempo

	if (delay->running == false) {               //Si el retarno no está en ejecución se inicia el retardo
		delay->startTime = currentTime;
		delay->running = true;
		return false;
	} else {
		tick_t timeElapsed = currentTime - delay->startTime;

		if (timeElapsed >= delay->duration) {    // Se implementan acciones cuando el retardo se cumple:
			delay->running = false;
			return true;
		} else {
			return false;                       // no se ha cumplido se retardo
		}
	}
}

//Funcion para asignar un nuevo retardo
void delayWrite(delay_t *delay, tick_t duration) {
	if (delay == NULL) {
		Error_Handler();
		return;
	}

	delay->duration = duration;

	// Reiniciar el retardo si estaba en ejecución
	if (delay->running == true) {
		delay->startTime = (tick_t) HAL_GetTick();
	}
}