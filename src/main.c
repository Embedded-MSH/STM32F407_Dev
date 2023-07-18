#include "main.h"

#include "key.h"
#include "led.h"


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == KEY1_Pin) {
        led_toggle(LED_RED);
    } else if (GPIO_Pin == KEY2_Pin) {
        led_toggle(LED_BLUE);
    } else if (GPIO_Pin == KEY3_Pin) {
        led_toggle(LED_BLUE);
        led_toggle(LED_RED);
    }
}

void SystemClock_Config(void);

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the
     * Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    led_init(LED_BLUE);
    led_init(LED_RED);
    key_init();
    while (1) { }

    return 0;
}
