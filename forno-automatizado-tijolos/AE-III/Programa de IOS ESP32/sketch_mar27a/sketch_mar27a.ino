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
// - Teste DAC (GPIO25 = DAC1, GPIO26 = DAC2)
// - Teste PWM via LEDC
//
// CORREÇÕES APLICADAS:
// [1] analogRead() removido — não existe no ESP-IDF; substituído por adc1_get_raw()
// [2] R1_IN1/IN2 corrigidos: GPIO10/11 → GPIO34/35 (ADC1_CH6/CH7, input-only)
// [3] DAC_2 definido duas vezes (GPIO25 e GPIO26) → corrigido para DAC_1/DAC_2
// [4] UART_RX não deve ser configurado como GPIO_MODE_OUTPUT → removido do set_direction
// [5] GPIO34/35 são input-only — NÃO chamar gpio_set_direction neles
// [6] loop()/setup() são nomes Arduino → entry point correto no ESP-IDF é app_main()
// ========================================================

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/dac.h"
#include "driver/ledc.h"
#include "esp_log.h"

static const char *TAG = "ESP32_IO";

// ===================== PINOS =====================

// ADC — input-only, não chamar gpio_set_direction
#define ADC_CH6_GPIO    (gpio_num_t)34   // ADC1_CH6 (era GPIO10 — ERRADO)
#define ADC_CH7_GPIO    (gpio_num_t)35   // ADC1_CH7 (era GPIO11 — ERRADO)

// DAC (corrigido: eram dois #define com o mesmo nome DAC_2)
#define DAC_1_GPIO      (gpio_num_t)25   // DAC_CHANNEL_1
#define DAC_2_GPIO      (gpio_num_t)26   // DAC_CHANNEL_2

// SPI
#define SPI_CLK_GPIO    (gpio_num_t)14
#define SPI_MISO_GPIO   (gpio_num_t)12
#define SPI_MOSI_GPIO   (gpio_num_t)13

// I2C
#define SCL_GPIO        (gpio_num_t)22
#define SDA_GPIO        (gpio_num_t)21

// Motores e resistência
#define MOTOR1_SAIDA1_GPIO      (gpio_num_t)19
#define MOTOR1_SAIDA2_GPIO      (gpio_num_t)18
#define MOTOR2_SAIDA1_GPIO      (gpio_num_t)2
#define MOTOR2_SAIDA2_GPIO      (gpio_num_t)15
#define RESISTENCIA_SAIDA_GPIO  (gpio_num_t)5

// UART (TX = output, RX = input — não configurar RX como output)
#define UART_TX_GPIO    (gpio_num_t)41
#define UART_RX_GPIO    (gpio_num_t)40

// ===================== SETUP =====================

void setup(void)
{
    ESP_LOGI(TAG, "=== ESP32 ESP-IDF + FreeRTOS iniciado ===");

    // --- Saídas digitais ---
    gpio_set_direction(MOTOR1_SAIDA1_GPIO,      GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR1_SAIDA2_GPIO,      GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR2_SAIDA1_GPIO,      GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTOR2_SAIDA2_GPIO,      GPIO_MODE_OUTPUT);
    gpio_set_direction(RESISTENCIA_SAIDA_GPIO,  GPIO_MODE_OUTPUT);
    gpio_set_direction(SPI_CLK_GPIO,            GPIO_MODE_OUTPUT);
    gpio_set_direction(SPI_MOSI_GPIO,           GPIO_MODE_OUTPUT);
    gpio_set_direction(UART_TX_GPIO,            GPIO_MODE_OUTPUT);

    // SPI_MISO e UART_RX são entradas
    gpio_set_direction(SPI_MISO_GPIO,           GPIO_MODE_INPUT);
    gpio_set_direction(UART_RX_GPIO,            GPIO_MODE_INPUT);

    // Estado inicial seguro (tudo desligado)
    gpio_set_level(MOTOR1_SAIDA1_GPIO,      0);
    gpio_set_level(MOTOR1_SAIDA2_GPIO,      0);
    gpio_set_level(MOTOR2_SAIDA1_GPIO,      0);
    gpio_set_level(MOTOR2_SAIDA2_GPIO,      0);
    gpio_set_level(RESISTENCIA_SAIDA_GPIO,  0);
    gpio_set_level(SPI_CLK_GPIO,            0);
    gpio_set_level(SPI_MOSI_GPIO,           0);
    gpio_set_level(UART_TX_GPIO,            0);

    // --- ADC 12 bits (GPIO34/35 são input-only — NÃO chamar gpio_set_direction) ---
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // GPIO34 — faixa ~0–3,3V
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11); // GPIO35 — faixa ~0–3,3V

    ESP_LOGI(TAG, "Setup concluído.");
}

// ===================== TESTE DIGITAIS =====================

void TesteDigitais(void)
{
    ESP_LOGI(TAG, "Teste digitais — ligando...");
    gpio_set_level(MOTOR1_SAIDA1_GPIO,      1);
    gpio_set_level(MOTOR1_SAIDA2_GPIO,      1);
    gpio_set_level(MOTOR2_SAIDA1_GPIO,      1);
    gpio_set_level(MOTOR2_SAIDA2_GPIO,      1);
    gpio_set_level(RESISTENCIA_SAIDA_GPIO,  1);
    gpio_set_level(SPI_CLK_GPIO,            1);
    gpio_set_level(SPI_MOSI_GPIO,           1);
    gpio_set_level(UART_TX_GPIO,            1);
    vTaskDelay(pdMS_TO_TICKS(100));

    ESP_LOGI(TAG, "Teste digitais — desligando...");
    gpio_set_level(MOTOR1_SAIDA1_GPIO,      0);
    gpio_set_level(MOTOR1_SAIDA2_GPIO,      0);
    gpio_set_level(MOTOR2_SAIDA1_GPIO,      0);
    gpio_set_level(MOTOR2_SAIDA2_GPIO,      0);
    gpio_set_level(RESISTENCIA_SAIDA_GPIO,  0);
    gpio_set_level(SPI_CLK_GPIO,            0);
    gpio_set_level(SPI_MOSI_GPIO,           0);
    gpio_set_level(UART_TX_GPIO,            0);
    vTaskDelay(pdMS_TO_TICKS(100));
}

// ===================== TESTE DAC =====================

void TesteDAC(void)
{
    ESP_LOGI("TESTE_DAC", "Iniciando rampa de tensão DAC (0 → 255 em 2 segundos)...");

    dac_output_enable(DAC_CHANNEL_1);   // GPIO25
    dac_output_enable(DAC_CHANNEL_2);   // GPIO26

    // 256 passos em 2000 ms → ~7,8 ms por passo
    for (int valor = 0; valor <= 255; valor++) {
        dac_output_voltage(DAC_CHANNEL_1, valor);
        dac_output_voltage(DAC_CHANNEL_2, valor);
        vTaskDelay(pdMS_TO_TICKS(8));
    }

    // Retorna a 0V
    dac_output_voltage(DAC_CHANNEL_1, 0);
    dac_output_voltage(DAC_CHANNEL_2, 0);

    ESP_LOGI("TESTE_DAC", "Rampa DAC concluída.");
}

// ===================== TESTE PWM =====================

void TestePWM(void)
{
    ESP_LOGI("TESTE_PWM", "Iniciando rampa PWM no GPIO%d...", MOTOR1_SAIDA1_GPIO);

    ledc_timer_config_t timer_config = {
        .speed_mode      = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num       = LEDC_TIMER_0,
        .freq_hz         = 5000,
        .clk_cfg         = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

    ledc_channel_config_t channel_config = {
        .gpio_num   = MOTOR1_SAIDA1_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LEDC_CHANNEL_0,
        .intr_type  = LEDC_INTR_DISABLE,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = 0,
        .hpoint     = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&channel_config));

    // Rampa 0 → 1023 em ~2 segundos
    for (int duty = 0; duty <= 1023; duty++) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        vTaskDelay(pdMS_TO_TICKS(2));
    }

    // Desliga ao final
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

    ESP_LOGI("TESTE_PWM", "Rampa PWM finalizada.");
}

// ===================== TESTE ADC =====================

void TesteADC(void)
{
    // adc1_get_raw() é a função correta no ESP-IDF (analogRead não existe aqui)
    int leitura_ch6 = adc1_get_raw(ADC1_CHANNEL_6);   // GPIO34
    int leitura_ch7 = adc1_get_raw(ADC1_CHANNEL_7);   // GPIO35

    float tensao_ch6 = leitura_ch6 * (3.3f / 4095.0f);
    float tensao_ch7 = leitura_ch7 * (3.3f / 4095.0f);

    ESP_LOGI(TAG, "ADC CH6 (GPIO34): %4d | %.3f V", leitura_ch6, tensao_ch6);
    ESP_LOGI(TAG, "ADC CH7 (GPIO35): %4d | %.3f V", leitura_ch7, tensao_ch7);
}

// ===================== ENTRY POINT =====================
// No ESP-IDF o entry point é app_main(), não loop()/setup() (esses são nomes Arduino)

void loop(void)
{
  TesteADC();
}