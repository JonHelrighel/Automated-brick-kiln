/*
 * adc.h
 *
 *  Created on: 16 de abr. de 2026
 *      Author: PC
 */

#ifndef MAIN_SRC_ADC_H_
#define MAIN_SRC_ADC_H_

#include <esp_adc/adc_oneshot.h>

#define CANAL_FIM_DE_CURSO 9 //gpio26
#define CANAL_TERMOPAR 8 //gpio25

void setup_ADC(adc_oneshot_unit_handle_t * adc);

uint16_t  printa_ADC(adc_oneshot_unit_handle_t * adc, uint8_t canal);

#endif /* MAIN_SRC_ADC_H_ */
