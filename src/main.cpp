#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
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
#ifdef __cplusplus
}
#endif /* __cplusplus */

void setLedBlue(bool state)
{
    if (!state)
        GPIOB->BSRR |= GPIO_BSRR_BS2;
    else
        GPIOB->BSRR |= GPIO_BSRR_BR2;
}

void setLedRed(bool state)
{
    if (!state)
        GPIOC->BSRR |= GPIO_BSRR_BS5;
    else
        GPIOC->BSRR |= GPIO_BSRR_BR5;
}

void sleepSecond(int second)
{
    for (int i = 0; i < second * 1000000; i++)
        __asm__("nop");
}

int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER &= ~GPIO_MODER_MODER5;
    GPIOC->MODER |= GPIO_MODER_MODER5_0;
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT_5;
    GPIOC->OTYPER |= (0 << 5);
    GPIOC->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR5;
    GPIOC->OSPEEDR |= (0 << 2 * 5);
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR5;
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR5_1;
    setLedRed(true);

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER &= ~GPIO_MODER_MODER2;
    GPIOB->MODER |= GPIO_MODER_MODER2_0;
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_2);
    GPIOB->OTYPER |= (0 << 2);
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR2;
    GPIOB->OSPEEDR |= (0 << 2 * 2);
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR2;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR2_1;
    setLedBlue(true);

    while (1) {
        setLedRed(false);
        setLedBlue(true);
        sleepSecond(2);
        setLedRed(true);
        setLedBlue(false);
        sleepSecond(2);
    }

    return 0;
}
