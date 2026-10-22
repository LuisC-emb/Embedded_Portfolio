#ifndef LED_H_
#define LED_H_

#include "gpio.h" // Importas tu librería de bajo nivel

// Definición del "Objeto" LED (Estructura)
typedef struct {
    GPIO_TypeDef *port;     // Puerto (ej. GPIOA)
    uint8_t pin;            // Número de pin (ej. 5)
    GPIO_Otype_t otype;     // Tipo de salida (Push-Pull / Open-Drain)
    GPIO_Pupd_t pupd;       // Pull-up / Pull-down
} LED_t;

// Métodos del objeto LED
void LED_Init(LED_t *led);
void LED_TurnOn(LED_t *led);
void LED_TurnOff(LED_t *led);
void LED_Toggle(LED_t *led);

#endif /* LED_H_ */
