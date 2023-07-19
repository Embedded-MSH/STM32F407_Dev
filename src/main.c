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


uint8_t usart1_rxData[5];
uint8_t usart2_rxData[5];
uint8_t usart3_rxData[5];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART1) {
        printf("USART1 接收到数据：%s\r\n", usart1_rxData);
        if (usart1_rxData[0] == 0x61) {
            led_toggle(LED_BLUE);
            printf("切换蓝灯\r\n");
        }
        if (usart1_rxData[0] == 0x62) {
            led_toggle(LED_RED);
            printf("切换红灯\r\n");
        }
        HAL_UART_Transmit_IT(&huart2, usart1_rxData, 5);
        // USART2_SendData(usart1_rxData, 5);
        HAL_UART_Receive_IT(&huart1, usart1_rxData, 5);
    } else if (huart->Instance == USART2) {
        printf("USART2 接收到数据：%s\r\n", usart1_rxData);
        HAL_UART_Transmit_IT(&huart3, usart2_rxData, 5);
        HAL_UART_Receive_IT(&huart2, usart2_rxData, 5);
    } else if (huart->Instance == USART3) {
        printf("USART3 接收到数据：%s\r\n", usart1_rxData);
        HAL_UART_Receive_IT(&huart3, usart3_rxData, 5);
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
    USART2_Init(115200);
    USART3_Init(115200);

    HAL_UART_Receive_IT(&huart1, usart1_rxData, 5);
    HAL_UART_Receive_IT(&huart2, usart2_rxData, 5);
    HAL_UART_Receive_IT(&huart3, usart3_rxData, 5);
    while (1) { }

    return 0;
}
