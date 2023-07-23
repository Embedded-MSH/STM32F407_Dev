#include "led.h"

void LedCtrl::init(LED_ID id)
{
    if (id > LED_TOTAL)
        return;
    if (id == LED_TOTAL) {
        for (int i = 0; i < LED_TOTAL; i++)
            initOneLed(static_cast<LED_ID>(i));
    } else {
        initOneLed(id);
    }
}

void LedCtrl::setLed(LED_ID id, LED_STATE state)
{
    if (id > LED_TOTAL)
        return;

    if (id == LED_TOTAL) {
        for (int i = 0; i < LED_TOTAL; i++)
            setOneLed(static_cast<LED_ID>(i), state);
    } else {
        setOneLed(id, state);
    }
}

void LedCtrl::toggleLed(LED_ID id)
{
    if (id > LED_TOTAL)
        return;
    if (id == LED_TOTAL) {
        for (int i = 0; i < LED_TOTAL; i++)
            toggleOneLed(static_cast<LED_ID>(i));
    } else {
        toggleOneLed(id);
    }
}

void LedCtrl::initOneLed(LED_ID id)
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

void LedCtrl::setOneLed(LED_ID id, LED_STATE state)
{
    GPIO_TypeDef* gpio_port = id == LED_BLUE ? LED_BLUE_GPIO : LED_RED_GPIO;
    unsigned int gpio_pin = id == LED_BLUE ? LED_BLUE_PIN : LED_RED_PIN;
    GPIO_PinState pin_state = state == LED_ON ? GPIO_PIN_RESET : GPIO_PIN_SET;
    HAL_GPIO_WritePin(gpio_port, gpio_pin, pin_state);
}

void LedCtrl::toggleOneLed(LED_ID id)
{
    GPIO_TypeDef* gpio_port = id == LED_BLUE ? LED_BLUE_GPIO : LED_RED_GPIO;
    unsigned int gpio_pin = id == LED_BLUE ? LED_BLUE_PIN : LED_RED_PIN;
    HAL_GPIO_TogglePin(gpio_port, gpio_pin);
}
