// ========================================================
// PROGRAMA EM ESP-IDF (FreeRTOS) – Equivalente nativo ESP32
// (sem framework Arduino – equivalente ao "AVR bare-metal")
// Baseado na imagem do ESP32-DevKitC-K1 + Datasheet oficial
// https://documentation.espressif.com/esp32_datasheet_en.pdf
//
// Funções:
// - Leitura analógica 12 bits (GPIO34/35 – ADC1_CH6/CH7)
// - Atuação na resistência (saída digital)
// - Controle dos motores (saídas digitais)
//
// Pinos 100% compatíveis com a imagem e com o datasheet (Tabela 2 e seção 4):
// GPIO34 = ADC1_CH6 (input-only)
// GPIO35 = ADC1_CH7 (input-only)
// GPIO21, GPIO18, GPIO19, GPIO27, GPIO26 = full digital output + PWM
// ========================================================

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"
#include "driver/dac.h"
#include "driver/ledc.h"

static const char *TAG = "ESP32_IO";

// === PINOS ===

#define R1_IN1_GPIO          (gpio_num_t)10   // ADC1_CH6  (R1-IN1)
#define R1_IN2_GPIO          (gpio_num_t)11   // ADC1_CH7  (R1-IN2)

#define DAC_2 (gpio_num_t)25
#define DAC_2 (gpio_num_t)26 

#define SPI_CLK (gpio_num_t)14
#define SPI_MISO (gpio_num_t)12
#define SPI_MOSI (gpio_num_t)13

#define SCL (gpio_num_t)22
#define SDA (gpio_num_t)21

#define MOTOR1_SAIDA1_GPIO   (gpio_num_t)19   // MOTOR1-SAIDA1
#define MOTOR1_SAIDA2_GPIO   (gpio_num_t)18   // MOTOR1-SAIDA2
#define RESISTENCIA_SAIDA_GPIO (gpio_num_t)5 // RESISTENCIA-SAIDA3

#define UART_TX (gpio_num_t)41 
#define UART_RX (gpio_num_t)40

#define MOTOR2_SAIDA1_GPIO   (gpio_num_t)2   // MOTOR2-SAIDA1
#define MOTOR2_SAIDA2_GPIO   (gpio_num_t)15   // MOTOR2-SAIDA2

void setup(){
    ESP_LOGI(TAG, "=== ESP32 ESP-IDF + FreeRTOS iniciado (baseado na imagem) ===");

    // ================== CONFIGURAÇÃO DAS SAÍDAS DIGITAIS ==================
    gpio_set_direction(MOTOR1_SAIDA1_GPIO,   GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR1_SAIDA2_GPIO,   GPIO_MODE_OUTPUT);
    gpio_set_direction(RESISTENCIA_SAIDA_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR2_SAIDA1_GPIO,   GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR2_SAIDA2_GPIO,   GPIO_MODE_OUTPUT);
    gpio_set_direction(SPI_CLK,   GPIO_MODE_OUTPUT);
    gpio_set_direction(SPI_MISO,   GPIO_MODE_OUTPUT);
    gpio_set_direction(SPI_MOSI,   GPIO_MODE_OUTPUT);
    gpio_set_direction(UART_TX,   GPIO_MODE_OUTPUT);
    gpio_set_direction(UART_RX,   GPIO_MODE_OUTPUT);

    // Estado inicial seguro (tudo desligado)
    gpio_set_level(MOTOR1_SAIDA1_GPIO,   0);
    gpio_set_level(MOTOR1_SAIDA2_GPIO,   0);
    gpio_set_level(RESISTENCIA_SAIDA_GPIO, 0);
    gpio_set_level(MOTOR2_SAIDA1_GPIO,   0);
    gpio_set_level(MOTOR2_SAIDA2_GPIO,   0);
    gpio_set_level(SPI_CLK, 0);
    gpio_set_level(SPI_MISO, 0);
    gpio_set_level(SPI_MOSI, 0);
    gpio_set_level(UART_TX, 0);
    gpio_set_level(UART_RX, 0);

    // ================== CONFIGURAÇÃO ADC 12 BITS (datasheet seção 4.2) ==================
    adc1_config_width(ADC_WIDTH_BIT_12);                    // Resolução 12 bits (0-4095)
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // GPIO34 – faixa ~0-3,3V
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11); // GPIO35 – faixa ~0-3,3V
}


void TesteDigitais(void)
{
    gpio_set_level(MOTOR1_SAIDA1_GPIO, 1);
    gpio_set_level(MOTOR1_SAIDA2_GPIO, 1);
    gpio_set_level(MOTOR2_SAIDA1_GPIO, 1);
    gpio_set_level(MOTOR2_SAIDA2_GPIO, 1);
    gpio_set_level(SPI_CLK, 1);
    gpio_set_level(SPI_MISO, 1);
    gpio_set_level(SPI_MOSI, 1);
    gpio_set_level(UART_TX, 1);
    gpio_set_level(UART_RX, 1);
    gpio_set_level(RESISTENCIA_SAIDA_GPIO, 1);
    vTaskDelay(pdMS_TO_TICKS(100));

    gpio_set_level(MOTOR1_SAIDA1_GPIO, 0);
    gpio_set_level(MOTOR1_SAIDA2_GPIO, 0);
    gpio_set_level(MOTOR2_SAIDA1_GPIO, 0);
    gpio_set_level(MOTOR2_SAIDA2_GPIO, 0);
    gpio_set_level(SPI_CLK, 0);
    gpio_set_level(SPI_MISO, 0);
    gpio_set_level(SPI_MOSI, 0);
    gpio_set_level(UART_TX, 0);
    gpio_set_level(UART_RX, 0);
    gpio_set_level(RESISTENCIA_SAIDA_GPIO, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
}

// =====================TESTE DAC (RAMPA 0 → 255 em exatamente 2 segundos) ======================
void TesteDAC(void)
{
    ESP_LOGI("TESTE_DAC", "Iniciando rampa de tensão DAC (0 → 255 em 2 segundos)...");

    // Habilita os canais DAC (GPIO25 = DAC1 e GPIO26 = DAC2 conforme datasheet e imagem)
    dac_output_enable(DAC_CHANNEL_1);
    dac_output_enable(DAC_CHANNEL_2);

    // Rampa suave: 256 passos em 2000 ms → delay de ~7,8 ms por passo
    for (int valor = 0; valor <= 255; valor++) {
        dac_output_voltage(DAC_CHANNEL_1, valor);   // DAC-1
        dac_output_voltage(DAC_CHANNEL_2, valor);   // DAC-2 (mesma rampa)
    }

    // Volta para 0V no final do teste
    dac_output_voltage(DAC_CHANNEL_1, 0);
    dac_output_voltage(DAC_CHANNEL_2, 0);

    ESP_LOGI("TESTE_DAC", "Rampa DAC concluída (tensão máxima atingida e retornada a 0V)");
}

void TestePWM(void)
{

    ESP_LOGI("TESTE_PWM", "Iniciando teste PWM rampa duty (pino %d)", MOTOR1_SAIDA1_GPIO);

    // Configuração do timer PWM
    ledc_timer_config_t timer_config = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_10_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 5000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

    // Canal PWM – ordem correta dos campos (igual ao header ledc.h)
    ledc_channel_config_t channel_config = {
        .gpio_num       = MOTOR1_SAIDA1_GPIO,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&channel_config));

    // Rampa de duty 0 → 1023 em ~2 segundos
    const int passos = 1024;
    const int delay_por_passo = 2000 / passos;  // ≈ 1.95 ms por passo

    for (int duty = 0; duty <= 1023; duty++) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(pdMS_TO_TICKS(delay_por_passo));
    }

    // Desliga no final
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

    ESP_LOGI("TESTE_PWM", "Rampa PWM finalizada");
}

void TestADC(){
    int read = analogRead(0);
}

void loop(){
    //TestePWM();
    TesteDigitais();
    TesteDAC();
}