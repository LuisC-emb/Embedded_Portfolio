#include "led.h"

// Inicializa el LED usando tu función de bajo nivel gpio_init_output
void LED_Init(LED_t *led) {
    gpio_init_output(led->port, led->pin, led->otype, led->pupd);
}

// Enciende el LED usando gpio_write_pin
void LED_TurnOn(LED_t *led) {
    gpio_write_pin(led->port, led->pin, GPIO_PIN_SET);
}

// Apaga el LED usando gpio_write_pin
void LED_TurnOff(LED_t *led) {
    gpio_write_pin(led->port, led->pin, GPIO_PIN_RESET);
}

// Cambia el estado del LED usando gpio_toggle_pin
void LED_Toggle(LED_t *led) {
    gpio_toggle_pin(led->port, led->pin);
}
