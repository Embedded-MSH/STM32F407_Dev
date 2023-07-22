#include "led.h"

#include <stm32f4xx_hal.h>


static void led_init_one(enum led_id id)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    GPIO_TypeDef* gpio_port = id == LED_BLUE ? LED_BLUE_GPIO : LED_RED_GPIO;
    unsigned int gpio_pin = id == LED_BLUE ? LED_BLUE_PIN : LED_RED_PIN;

    if (gpio_port == GPIOB)
        __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (gpio_port == GPIOC)
        __HAL_RCC_GPIOC_CLK_ENABLE();

    HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = gpio_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(gpio_port, &GPIO_InitStruct);
}


static void led_set_one(enum led_id id, enum led_state state)
{
    GPIO_TypeDef* gpio_port = id == LED_BLUE ? LED_BLUE_GPIO : LED_RED_GPIO;
    unsigned int gpio_pin = id == LED_BLUE ? LED_BLUE_PIN : LED_RED_PIN;
    GPIO_PinState pin_state = state == LED_ON ? GPIO_PIN_RESET : GPIO_PIN_SET;
    HAL_GPIO_WritePin(gpio_port, gpio_pin, pin_state);
}


static void led_toggle_one(enum led_id id)
{
    GPIO_TypeDef* gpio_port = id == LED_BLUE ? LED_BLUE_GPIO : LED_RED_GPIO;
    unsigned int gpio_pin = id == LED_BLUE ? LED_BLUE_PIN : LED_RED_PIN;
    HAL_GPIO_TogglePin(gpio_port, gpio_pin);
}

void led_init(enum led_id id)
{
    if (id > LED_TOTAL)
        return;
    if (id == LED_TOTAL) {
        for (int i = 0; i < LED_TOTAL; i++)
            led_init_one(i);
    } else {
        led_init_one(id);
    }
}



void led_set(enum led_id id, enum led_state state)
{
    if (id > LED_TOTAL)
        return;

    if (id == LED_TOTAL) {
        for (int i = 0; i < LED_TOTAL; i++)
            led_set_one(i, state);
    } else {
        led_set_one(id, state);
    }
}

void led_toggle(enum led_id id)
{
    if (id > LED_TOTAL)
        return;
    if (id == LED_TOTAL) {
        for (int i = 0; i < LED_TOTAL; i++)
            led_toggle_one(i);
    } else {
        led_toggle_one(id);
    }
}
