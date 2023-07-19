#include "main.h"

#include "key.h"
#include "led.h"
#include "usart.h"

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


uint8_t rxData = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{

    HAL_UART_Transmit(&huart1, (uint8_t*)&rxData, 1, 10000);
    if (huart->Instance == USART1) {
        if (rxData == 0x61) {
            led_toggle(LED_BLUE);
            HAL_UART_Transmit(&huart1,
                              (uint8_t*)"Toggle LED0!\r\n",
                              sizeof("Toggle LED0!\r\n"),
                              10000);
        }
        if (rxData == 0x62) {
            led_toggle(LED_RED);
            HAL_UART_Transmit(&huart1,
                              (uint8_t*)"Toggle LED1!\r\n",
                              sizeof("Toggle LED1!\r\n"),
                              10000);
        }

        HAL_UART_Receive_IT(&huart1, &rxData, 1);
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
    USART1_Init(115200);

    HAL_UART_Receive_IT(&huart1, &rxData, 1);
    while (1) {
        // HAL_UART_Transmit(&huart1,
        //                   (uint8_t*)"Toggle LED1!\r\n",
        //                   sizeof("Toggle LED1!\r\n"),
        //                   10000);
    }

    return 0;
}
