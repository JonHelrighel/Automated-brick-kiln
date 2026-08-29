/*
 * definicao_de_pinos.h
 *
 *  Created on: 13 de abr. de 2026
 *      Author: Gabriel
 */

#ifndef MAIN_SRC_DEFINICAO_DE_PINOS_H_
#define MAIN_SRC_DEFINICAO_DE_PINOS_H_

#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "soc/gpio_num.h"

#define DEBUG 0

#define PINO_LIGA GPIO_NUM_5
#define PINO_INICIAR GPIO_NUM_22
#define PINO_MOTOR_E GPIO_NUM_19
#define PINO_MOTOR_D GPIO_NUM_18

void setup_pinos(){
	gpio_set_direction(PINO_LIGA, GPIO_MODE_INPUT);
	gpio_set_direction(PINO_INICIAR, GPIO_MODE_INPUT);
	gpio_set_direction(PINO_MOTOR_D, GPIO_MODE_OUTPUT);
	gpio_set_direction(PINO_MOTOR_E, GPIO_MODE_OUTPUT);
}

#endif /* MAIN_SRC_DEFINICAO_DE_PINOS_H_ */
