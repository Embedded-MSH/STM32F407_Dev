#include "main.h"

#include "Led.h"
extern "C"
{
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
}

void sleepSecond(int second)
{
    HAL_Delay(second * 1000);
}


// This prevent name mangling for functions used in C/assembly files.
extern "C"
{
    void SysTick_Handler(void)
    {
        HAL_IncTick();   // SysTick定时器是由HAL库进行管理的,用于生成系统滴答定时和延时函数。HAL需要通过重写SysTick
                         // 调用 IncTick 获取滴答。

        // 1 Hz blinking
        if ((HAL_GetTick() % 1000) == 0) {
            LedCtrl::instance()->toggleLed(LedCtrl::LED::RED);
            LedCtrl::instance()->toggleLed(LedCtrl::LED::BLUE);
        }
    }
}

int main(void)
{
    HAL_StatusTypeDef ret = HAL_Init();
    if (ret != HAL_OK) {
        while (1) { }
    }
    auto ledctrl = LedCtrl::instance();
    ledctrl->init(LedCtrl::LED::RED);
    ledctrl->init(LedCtrl::LED::BLUE);

    HAL_SYSTICK_Config(SystemCoreClock / 1000);
    while (1) { }

    return 0;
}
