#include "exti.h"

void exti_init(GPIO_TypeDef *port, uint8_t pin, GPIO_Pupd_t pull_type, EXTI_Trigger_t trigger) {
    // 1. Enable SYSCFG clock
    RCC->APB2ENR |= (0x1U << 14);

    // 2. Configure the corresponding pin as input using your GPIO driver
    gpio_init_input(port, pin, pull_type);

    // 3. Connect the GPIO pin to its corresponding EXTI line via SYSCFG_EXTICR
    // SYSCFG has 4 EXTICR registers, each handling 4 pins (4 bits per pin)
    uint8_t exticr_index = pin / 4;
    uint8_t exticr_position = (pin % 4) * 4;

    // Determine port mapping value (GPIOA = 0, GPIOB = 1, GPIOC = 2, etc.)
    uint8_t port_value = 0U;
    if      (port == GPIOA) port_value = 0x0U;
    else if (port == GPIOB) port_value = 0x1U;
    else if (port == GPIOC) port_value = 0x2U;
    else if (port == GPIOH) port_value = 0x7U;

    // Clear and set the correct bits in SYSCFG->EXTICR
    SYSCFG->EXTICR[exticr_index] &= ~(0xFU << exticr_position);
    SYSCFG->EXTICR[exticr_index] |=  (port_value << exticr_position);

    // 4. Configure EXTI line trigger mask (Interrupt Mask Register)
    EXTI->IMR |= (0x1U << pin);

    // 5. Configure trigger selection (Rising / Falling)
    if (trigger == EXTI_TRIGGER_RISING || trigger == EXTI_TRIGGER_BOTH) {
        EXTI->RTSR |= (0x1U << pin);
    } else {
        EXTI->RTSR &= ~(0x1U << pin);
    }

    if (trigger == EXTI_TRIGGER_FALLING || trigger == EXTI_TRIGGER_BOTH) {
        EXTI->FTSR |= (0x1U << pin);
    } else {
        EXTI->FTSR &= ~(0x1U << pin);
    }

    // 6. Enable the corresponding IRQ in the NVIC
    // EXTI lines 0 to 4 have dedicated IRQ numbers (6 to 10)
    // Lines 5 to 9 share EXTI9_5_IRQn (23), Lines 10 to 15 share EXTI15_10_IRQn (40)
    int irq_number = 0;
    if (pin == 0)      irq_number = 6;
    else if (pin == 1) irq_number = 7;
    else if (pin == 2) irq_number = 8;
    else if (pin == 3) irq_number = 9;
    else if (pin == 4) irq_number = 10;
    else if (pin >= 5 && pin <= 9)   irq_number = 23;
    else if (pin >= 10 && pin <= 15) irq_number = 40;

    NVIC_SetPriority(irq_number, 2);
    NVIC_EnableIRQ(irq_number);
}
