#include "MAX31865_lib.h"

// The 'nominal' 0-degrees-C resistance of the sensor 100.0 for PT100, 1000.0 for PT1000
#define MAX31865_PT100_R0 (double)100.0

// The value of the Rref resistor. Use 428.5 for PT100 and 4285.0 for PT1000
#define MAX31865_Rref (double)428.5


bool MAX31865_Sensor_Error = 0; // Error Status

void cs_set();
void cs_reset();

extern SPI_HandleTypeDef hspi1;

void MAX31865_Init(uint8_t num_wires) {
	MAX31865_Sensor_Error = 0;
	uint8_t MAX31865_Configuration_register_write[] = { 0x80, 0x00 };

	// RTD configuration according to the number of threads
	if (num_wires == 2 || num_wires == 4) {
		MAX31865_Configuration_register_write[1] = 0xC2;
	} else if (num_wires == 3) {
		MAX31865_Configuration_register_write[1] = 0xD2;
	}

	// Send configuration bytes to max31865
	cs_set();
	HAL_SPI_Transmit(&hspi1, MAX31865_Configuration_register_write, 2, 100);
	cs_reset();

	if (MAX31865_Configuration_info() == 0xD0) {
		printf("\rInitialization MAX31865 OK\r\n");
	} else {
		// as long as the max31865 has not been configured correctly it keeps trying indefinitely
		while (MAX31865_Configuration_info() != 0xD0) {
			cs_set();
			HAL_SPI_Transmit(&hspi1, MAX31865_Configuration_register_write, 2,100);
			cs_reset();
			if (MAX31865_Configuration_info() == 0xD0) {
				printf("\rInitialization MAX31865 OK\r\n");
				break;
			}
		}
	}
}

// Get max31865 configuration info
uint8_t MAX31865_Configuration_info(void) {
	uint8_t read_data = 0x00;
	uint8_t MAX31865_Configuration = 0x00;
	cs_set();
	HAL_SPI_Transmit(&hspi1, &read_data, 1, 100);
	HAL_SPI_Receive(&hspi1, &MAX31865_Configuration, 1, 100);
	cs_reset();
	return MAX31865_Configuration;
}

// Get Temperature
double MAX31865_Get_Temperature(void) {
	double data;

	struct rx_data_MAX31865 {
		uint16_t RTD_Resistance_Registers;
		uint16_t High_Fault_Threshold;
		uint16_t Low_Fault_Threshold;
		uint8_t Fault_Status;
	};

	struct rx_data_MAX31865 MAX31865_receieve_data;

	uint8_t MAX31865_start_address_of_the_poll = 0x01;
	uint8_t MAX31865_rx_buffer[7];

	cs_set();
	HAL_SPI_Transmit(&hspi1, &MAX31865_start_address_of_the_poll, 1, 100); // Sends the address of the register from which the data is read
	HAL_SPI_Receive(&hspi1, MAX31865_rx_buffer, 7, 100); // Get All Data
	cs_reset();

	// assigns information to each regiter in the structure
	MAX31865_receieve_data.RTD_Resistance_Registers = ((MAX31865_rx_buffer[0]
			<< 8) | MAX31865_rx_buffer[1]) >> 1;
	MAX31865_receieve_data.High_Fault_Threshold = ((MAX31865_rx_buffer[2] << 8)
			| MAX31865_rx_buffer[3]) >> 1;
	MAX31865_receieve_data.Low_Fault_Threshold = (MAX31865_rx_buffer[4] << 8)
			| MAX31865_rx_buffer[5];
	MAX31865_receieve_data.Fault_Status = MAX31865_rx_buffer[6];

	// error handling
	if (MAX31865_receieve_data.Fault_Status > 0x00) {

		MAX31865_Sensor_Error = 1;
		printf("\rSensor Error!\r\n");

		/*----Automatic error reset ----*/
		// Module is reset
		MAX31865_Init(3);
		MAX31865_Sensor_Error = 0;
	}

	// convert ADC values to resistance
	data = ((double) MAX31865_receieve_data.RTD_Resistance_Registers
			* MAX31865_Rref ) / (double) 32768.0; // ADC resolution 15 bits
	//printf("\rRrtd = %d\n", (int) data);

	// converts and returns temperature values
	return MAX31865_Get_Temperature_math(data);
}

// Conversion of resistance to temperature
double MAX31865_Get_Temperature_math(double PT100_Resistance) {
	double MAX31865_PT100_T = 0.0;

	//If the resistance is high (greater than or equal to 100 ohms) use:
	if (PT100_Resistance >= (double) 100.0) {
		double MAX31865_math_Discriminant = (double) 0.00001527480889
				- ((double) -0.00000231
						* (1 - (PT100_Resistance / MAX31865_PT100_R0 )));
		MAX31865_PT100_T = ((double) -0.0039083
				+ sqrt(MAX31865_math_Discriminant)) / (double) -0.000001155;
		// If the resistance is low (less than 100 ohms), another polynomial formula is used to calculate the temperature.
	} else {
		MAX31865_PT100_T = (double) 0.000000000270 * pow(PT100_Resistance, 5)
				- (double) 0.000000066245 * pow(PT100_Resistance, 4)
				- (double) 0.000000184636 * pow(PT100_Resistance, 3)
				+ (double) 0.002320232987 * pow(PT100_Resistance, 2)
				+ (double) 2.229927824035 * PT100_Resistance
				- (double) 242.090854986215;
	}
	return MAX31865_PT100_T;
}

// CS GND
void cs_set() {
	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_RESET);
}

// CS VDD
void cs_reset() {
	HAL_GPIO_WritePin(GPIOA, CS_Pin, GPIO_PIN_SET);
}