#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs e botão
#define LED_VERMELHO 13
#define LED_AZUL 11
#define LED_VERDE 12
#define BOTAO 5

#define DEBOUNCE_TIME 300  // Tempo de debounce
#define DELAY_TEMPO 3000   // Tempo de atraso de 3 segundos

// Variáveis globais
volatile bool botao_pressionado = false;
volatile uint32_t lastPressTime = 0;

// Declaração das funções de callback
int64_t desligar_led_azul_callback(alarm_id_t id, void *user_data);
int64_t desligar_led_vermelho_callback(alarm_id_t id, void *user_data);
int64_t desligar_led_verde_callback(alarm_id_t id, void *user_data);

// Callbacks para desligamento sequencial dos LEDs após o botão ser pressionado
int64_t desligar_led_azul_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, 0);
    add_alarm_in_ms(DELAY_TEMPO, desligar_led_vermelho_callback, NULL, false);
    return 0;
}

int64_t desligar_led_vermelho_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, 0);
    add_alarm_in_ms(DELAY_TEMPO, desligar_led_verde_callback, NULL, false);
    return 0;
}

int64_t desligar_led_verde_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, 0);
    botao_pressionado = false; // Permite que o botão seja pressionado novamente
    return 0;
}

// Interrupção do botão
void gpio_callback(uint gpio, uint32_t events) {
    uint32_t currentTime = to_ms_since_boot(get_absolute_time());
    if (currentTime - lastPressTime < DEBOUNCE_TIME || botao_pressionado) return;
    lastPressTime = currentTime;
    botao_pressionado = true;
    
    gpio_put(LED_VERDE, 1);
    gpio_put(LED_AZUL, 1);
    gpio_put(LED_VERMELHO, 1);
    add_alarm_in_ms(DELAY_TEMPO, desligar_led_azul_callback, NULL, false);
}

int main() {

    // Configuração dos LEDs
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    // Configuração do botão
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    
    while (true) {
        sleep_ms(1000);
    }
}
