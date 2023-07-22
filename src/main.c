#include "main.h"

#include "key.h"
#include "led.h"
#include "usart.h"

#include <string.h>

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == KEY1_Pin) {
        printf("KEY1 被按下\n");
        USART3_SendString("STM32 ON");
        led_set(LED_RED, LED_ON);
    } else if (GPIO_Pin == KEY2_Pin) {
        printf("KEY2 被按下\n");
        USART3_SendString("STM32 OFF");
        led_set(LED_RED, LED_OFF);
    } else if (GPIO_Pin == KEY3_Pin) {
        printf("KEY3 被按下\r\n");
        HAL_UART_Transmit_IT(&huart3, (uint8_t*)"status\r\n", 9);
        led_toggle(LED_BLUE);
        led_toggle(LED_RED);
    }
}
#define REC_LENGTH 1
#define MAX_REC_LENGTH 1024

unsigned char UART1_Rx_Buf[MAX_REC_LENGTH];
unsigned int UART1_Rx_cnt;
unsigned char UART1_temp[REC_LENGTH];

unsigned char UART2_Rx_Buf[MAX_REC_LENGTH];
unsigned int UART2_Rx_cnt;
unsigned char UART2_temp[REC_LENGTH];

unsigned char UART3_Rx_Buf[MAX_REC_LENGTH];
unsigned int UART3_Rx_cnt;
unsigned char UART3_temp[REC_LENGTH];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART1) {
        UART1_Rx_Buf[UART1_Rx_cnt] = UART1_temp[0];
        UART1_Rx_cnt++;
        if (0x0a == UART1_temp[0]) {
            HAL_UART_Transmit(&huart1,
                              UART1_Rx_Buf,
                              UART1_Rx_cnt,
                              0x10);   // 发送接收到的数据
            for (int i = 0; i < UART1_Rx_cnt; i++)
                UART1_Rx_Buf[i] = 0;
            UART1_Rx_cnt = 0;
        }
        HAL_UART_Receive_IT(&huart1, (uint8_t*)UART1_temp, REC_LENGTH);
    } else if (huart->Instance == USART2) {
        UART2_Rx_Buf[UART2_Rx_cnt] = UART2_temp[0];
        UART2_Rx_cnt++;
        if (0x0a == UART2_temp[0]) {
            HAL_UART_Transmit(&huart2,
                              UART2_Rx_Buf,
                              UART2_Rx_cnt,
                              0x10);   // 发送接收到的数据
            for (int i = 0; i < UART2_Rx_cnt; i++)
                UART2_Rx_Buf[i] = 0;
            UART2_Rx_cnt = 0;
        }
        HAL_UART_Receive_IT(&huart2, (uint8_t*)UART2_temp, REC_LENGTH);
    } else if (huart->Instance == USART3) {
        UART3_Rx_Buf[UART3_Rx_cnt] = UART3_temp[0];
        UART3_Rx_cnt++;
        if (0x0a == UART3_temp[0]) {
            if (UART3_Rx_Buf[0] == 'H' && UART3_Rx_Buf[1] == 'A'
                && UART3_Rx_Buf[2] == 'O' && UART3_Rx_Buf[3] == 'N') {
                led_set(LED_RED, LED_ON);
            } else if (UART3_Rx_Buf[0] == 'H' && UART3_Rx_Buf[1] == 'A'
                       && UART3_Rx_Buf[2] == 'O' && UART3_Rx_Buf[3] == 'F'
                       && UART3_Rx_Buf[4] == 'F') {
                led_set(LED_RED, LED_OFF);
            }
            memset(UART3_Rx_Buf, 0x0, UART3_Rx_cnt);
            UART3_Rx_cnt = 0;
        }
        HAL_UART_Receive_IT(&huart3, (uint8_t*)UART3_temp, REC_LENGTH);
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
    // USART2_Init(115200);
    USART3_Init(115200);

    HAL_UART_Receive_IT(&huart1, UART1_temp, REC_LENGTH);
    // HAL_UART_Receive_IT(&huart2, UART2_temp, REC_LENGTH);
    HAL_UART_Receive_IT(&huart3, UART2_temp, REC_LENGTH);
    while (1) {
        led_toggle(LED_BLUE);
        sleepSecond(0.5);
    }

    return 0;
}
