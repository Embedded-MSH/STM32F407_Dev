#include "Led.h"


LedCtrl::LedCtrl()
{
    m_gpioName[LED::RED] = std::make_pair(GPIOC, GPIO_PIN_5);
    m_gpioName[LED::BLUE] = std::make_pair(GPIOB, GPIO_PIN_2);
}


bool LedCtrl::init(LED led)
{
    if (m_gpioName.find(led) == m_gpioName.end())
        return false;
    auto gpioName = m_gpioName[led].first;
    auto gpioPin = m_gpioName[led].second;

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    if (gpioName == GPIOB)
        __HAL_RCC_GPIOB_CLK_ENABLE();
    else
        __HAL_RCC_GPIOC_CLK_ENABLE();

    HAL_GPIO_WritePin(gpioName, gpioPin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = gpioPin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(gpioName, &GPIO_InitStruct);
    return true;
}

void LedCtrl::setLed(LED led, bool state)
{
    if (m_gpioName.find(led) == m_gpioName.end())
        return;
    auto gpioName = m_gpioName[led].first;
    auto gpioPin = m_gpioName[led].second;
    if (!state)
        HAL_GPIO_WritePin(gpioName, gpioPin, GPIO_PIN_RESET);
    else
        HAL_GPIO_WritePin(gpioName, gpioPin, GPIO_PIN_SET);
}

void LedCtrl::toggleLed(LED led)
{
    if (m_gpioName.find(led) == m_gpioName.end())
        return;
    auto gpioName = m_gpioName[led].first;
    auto gpioPin = m_gpioName[led].second;
    HAL_GPIO_TogglePin(gpioName, gpioPin);
}
