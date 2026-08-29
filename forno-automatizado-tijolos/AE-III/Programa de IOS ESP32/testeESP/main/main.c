#include "hal/gpio_types.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <driver/gpio.h>
#include <esp_adc/adc_oneshot.h>

void app_main(void)
{
	gpio_set_direction(2, GPIO_MODE_OUTPUT);
	
	adc_oneshot_unit_handle_t adc1_handle;
	adc_oneshot_unit_init_cfg_t init_config1 = {
	    .unit_id = ADC_UNIT_1,
	    .ulp_mode = ADC_ULP_MODE_DISABLE,
	};
	
	adc_oneshot_new_unit(&init_config1, &adc1_handle);
	
	adc_oneshot_chan_cfg_t config = {
	    .bitwidth = ADC_BITWIDTH_DEFAULT,
	    .atten = ADC_ATTEN_DB_12,
	};
	
	adc_oneshot_config_channel(adc1_handle, 0, &config);
	
	int adc_read = 10;
	uint8_t input = 0;
	
    while (true) {
		adc_oneshot_read(adc1_handle, 0, &adc_read);
        printf("valor ADC: %d\n", adc_read);
        usleep(100000);
    }
}
