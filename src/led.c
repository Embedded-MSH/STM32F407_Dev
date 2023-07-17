#include "led.h"

#include <stm32f4xx_hal.h>
void led_init(enum led_id id)
{
    if (id >= LED_TOTAL)
        return;

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    GPIO_TypeDef* gpio_port = id == LED_BLUE ? GPIOB : GPIOC;
    unsigned int gpio_pin = id == LED_BLUE ? GPIO_PIN_2 : GPIO_PIN_5;

    if (gpio_port == GPIOB)
        __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (gpio_port == GPIOC)
        __HAL_RCC_GPIOC_CLK_ENABLE();
    else
        while (1) {
            __asm("nop");
        }

    HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = gpio_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(gpio_port, &GPIO_InitStruct);
}

void led_set(enum led_id id, enum led_state state)
{
    if (id >= LED_TOTAL)
        return;

    GPIO_TypeDef* gpio_port = id == LED_BLUE ? GPIOB : GPIOC;
    unsigned int gpio_pin = id == LED_BLUE ? GPIO_PIN_2 : GPIO_PIN_5;

    GPIO_PinState pin_state = state == LED_ON ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(gpio_port, gpio_pin, pin_state);
}

void led_toggle(enum led_id id)
{
    if (id >= LED_TOTAL)
        return;
    GPIO_TypeDef* gpio_port = id == LED_BLUE ? GPIOB : GPIOC;
    unsigned int gpio_pin = id == LED_BLUE ? GPIO_PIN_2 : GPIO_PIN_5;
    HAL_GPIO_TogglePin(gpio_port, gpio_pin);
}
