/*
 * adc.c
 *
 *  Created on: 16 de abr. de 2026
 *      Author: PC
 */
#include "adc.h"
#include "esp_adc/adc_oneshot.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/_types.h>
#include "temporizador.h"
 
 void setup_ADC(adc_oneshot_unit_handle_t * adc){
 	
 	adc_oneshot_unit_init_cfg_t init_config1 = {
 		.unit_id = ADC_UNIT_2,
 		.ulp_mode = ADC_ULP_MODE_DISABLE
 	};
 	
 	adc_oneshot_new_unit(&init_config1, adc);
 	
 	adc_oneshot_chan_cfg_t config = {		
 		.bitwidth = ADC_BITWIDTH_DEFAULT,
 		.atten = ADC_ATTEN_DB_0
 	};
 	
 	adc_oneshot_config_channel(*adc, CANAL_FIM_DE_CURSO, &config);
	adc_oneshot_config_channel(*adc, CANAL_TERMOPAR, &config);
 }
 
uint16_t printa_ADC(adc_oneshot_unit_handle_t * adc, uint8_t canal){
	int adc_leitura;
	adc_oneshot_read(*adc, canal,&adc_leitura);
	
	uint16_t tempo = (horas * 60 * 60) + (minutos * 60) + segundos;
	
	printf("%d,%d\n", tempo,adc_leitura);
	
	return tempo;
}
