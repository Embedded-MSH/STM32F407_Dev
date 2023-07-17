#include "main.h"

#include "led.h"


void sleepSecond(int second)
{
    HAL_Delay(second * 1000);
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
