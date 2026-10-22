#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f410rb.h"
#include "gpio.h"

// Trigger selection enum
typedef enum {
    EXTI_TRIGGER_FALLING = 0x01U,
    EXTI_TRIGGER_RISING  = 0x02U,
    EXTI_TRIGGER_BOTH    = 0x03U
} EXTI_Trigger_t;

// Function Prototypes for generic EXTI configuration
void exti_init(GPIO_TypeDef *port, uint8_t pin, GPIO_Pupd_t pull_type, EXTI_Trigger_t trigger);

#endif /* EXTI_H_ */
