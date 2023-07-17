#include "main.h"

#include "led.h"


void _close(void)
{
}
void _lseek(void)
{
}
void _read(void)
{
}
void _write(void)
{
}
void _kill(void)
{
}
void _getpid(void)
{
}

void setLedBlue(int state)
{
    if (!state)
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
    else
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
}

void setLedRed(int state)
{
    if (!state)
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
    else
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
}

void sleepSecond(int second)
{
    HAL_Delay(second * 1000);
}


void GPIOC5_REDLED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    __HAL_RCC_GPIOC_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void GPIOB2_BLUELED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void SysTick_Handler(void)
{
    HAL_IncTick();   // SysTick定时器是由HAL库进行管理的,用于生成系统滴答定时和延时函数。HAL需要通过重写SysTick
                     // 调用 IncTick 获取滴答。

    // 1 Hz blinking
    if ((HAL_GetTick() % 500) == 0) {
        led_toggle(LED_RED);
        led_toggle(LED_BLUE);
    }
}

int main(void)
{
    HAL_StatusTypeDef ret = HAL_Init();
    if (ret != HAL_OK) {
        while (1) { }
    }
    led_init(LED_BLUE);
    led_init(LED_RED);

    HAL_SYSTICK_Config(SystemCoreClock / 1000);
    while (1) { }

    return 0;
}
